#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include"../../Objects/GameObjectManager.h"
#include <Windows.h>
#include<time.h>

InGameScene::InGameScene():
	object_manager(nullptr),
	player(),
	main_handle(0)
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
	backgound_UI = rm->GetImages("Resource/Images/backgound_UI.png")[0];
	background = rm->GetImages("Resource/Images/haikei.png")[0];

	numbers_image[0] = rm->GetImages("Resource/Images/number0.png")[0];
	numbers_image[1] = rm->GetImages("Resource/Images/number1.png")[0];
	numbers_image[2] = rm->GetImages("Resource/Images/number2.png")[0];
	numbers_image[3] = rm->GetImages("Resource/Images/number3.png")[0];
	numbers_image[4] = rm->GetImages("Resource/Images/number4.png")[0];
	numbers_image[5] = rm->GetImages("Resource/Images/number5.png")[0];
	numbers_image[6] = rm->GetImages("Resource/Images/number6.png")[0];
	numbers_image[7] = rm->GetImages("Resource/Images/number7.png")[0];
	numbers_image[8] = rm->GetImages("Resource/Images/number8.png")[0];
	numbers_image[9] = rm->GetImages("Resource/Images/number9.png")[0];
	numbers_image[10] = 0;
	syuriken = rm->GetImages("Resource/Images/syuriken1.png")[0];
}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{

	main_handle = LoadSoundMem("Resource/sound/main.mp3");

	if (main_handle != -1)
	{
		PlaySoundMem(main_handle, DX_PLAYTYPE_LOOP);
	}

	srand(time(NULL));

	//GameObjectManagerインスタンス取得
	object_manager = new GameObjectManager();

	//プレイヤー生成
	player = object_manager->CreateGameObject<Player>(Vector2D(0, 0));


	// ブロック生成
	//CreateBlock1();
	const int rows = 4;
	const int cols = 9;

	float startX = 80.0f;
	float startY = 100.0f;

	float blockWidth = 100.0f;
	float blockHeight = 50.0f;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			Vector2D pos(
				startX + x * (blockWidth + 10),
				startY + y * (blockHeight + 10)
			);

			object_manager->CreateGameObject<Block>(pos);
			screen_block1++;
		}
	}

	// 生成セット
	Block2* obj = nullptr;
	float x = 0;
	float z = 0;
	int place = GetRand(1) + 0;
	if (place == 0)
	{
		x = 0;
		z = 1;
	}

	else if (place == 1)
	{
		x = 1020;
		z = -1;
	}

	obj =  object_manager->CreateGameObject<Block2>(Vector2D(x, 60.0));
	obj->SetVelocity(Vector2D(z, 0));


	// ボール生成
	player->SetInstance(object_manager);
	player->CreateBall();
}

eSceneType InGameScene::Update(const float& delta_second)
{

	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//入力情報の更新
	input->Update();

	//ゲームを終了
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	// 決定
	if (input->GetKeyDown(KEY_INPUT_E))
	{
		return eSceneType::eResult;
	}

	Animation(delta_second);

	// オブジェクトリストループ
	ObjectListLoop(delta_second);

	// ボールが無くなれば終了する
	if (have_ball < 0)
	{
		next_count += delta_second;
		if (next_count > 1.0f)
			return eSceneType::eResult;
	}

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	float font = 0;		//数字サイズ
	int x_start = 0;	//
	int y_start = 0;	//
	int x_size = 0;		//

	//背景描画
	DrawRotaGraph(640, 360, 1.0, 0.0, background, true, false);

	int n = 0;	//オブジェクト数カウント
	for (GameObject* obj : scene_objects_list)
	{
		obj->Draw(Vector2D(0, 0), true);
		n++;
	}
	//DrawBox(1051, 0, D_WIN_MAX_X, D_WIN_MAX_Y, 0x000000, true);	//UIゾーン用隠し

	

	//UI背景
	DrawRotaGraph(1165, 370, 1.15, 0.0, backgound_UI, true, false, false);
	

	// スコア描画
	font = 0.2;	x_start = 1080;	y_start = 280;	x_size = 30;
	DrawFormatString(x_start, y_start - 80, 0x000000, "スコア");
	DrawRotaGraphF(x_start + x_size * 5, y_start, font, 0.0, numbers_image[draw_number[0]], true, false);
	DrawRotaGraphF(x_start + x_size * 4, y_start, font, 0.0, numbers_image[draw_number[1]], true, false);
	DrawRotaGraphF(x_start + x_size * 3, y_start, font, 0.0, numbers_image[draw_number[2]], true, false);
	DrawRotaGraphF(x_start + x_size * 2, y_start, font, 0.0, numbers_image[draw_number[3]], true, false);
	DrawRotaGraphF(x_start + x_size * 1, y_start, font, 0.0, numbers_image[draw_number[4]], true, false);

	// 手裏剣描画
	x_start = 1100;	y_start = 430;	x_size = 60;
	DrawFormatString(x_start - 40, y_start - 80, 0x000000, "手裏剣数");
	//DrawFormatString(1080, 550, 0x000000, "  %d", have_ball);
	for (int i = 0; i < have_ball; i++)
		DrawRotaGraphF(x_start + x_size * i, y_start, 0.3, π / 4, syuriken, true, false);


	DrawFormatString(1080, 650, 0x000000, "  %d", stage_level);
}

void InGameScene::Finalize()
{

	//リザルトデータの書き込み
	FILE* fp = nullptr;
	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/save/result_data.csv", "w");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/save/result_dat.csvが開けません\n");
	}

	//スコアを保存
	fprintf(fp, "%d,\n", score);

	//アイテム
	fprintf(fp, "%d,\n", item);

	//マト
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", mato[i]);
	}

	//ファイルクローズ
	fclose(fp);


	if (main_handle != -1)
	{
		StopSoundMem(main_handle);
		DeleteSoundMem(main_handle);
	}
}

eSceneType InGameScene::GetNowSceneType()const
{
	return eSceneType::eInGame;
}

void InGameScene::Animation(const float& delta_second)
{
	// スコアアニメ
	draw_number[0] = ((((score % 10000) % 1000) % 100) % 10);
	if (score >= 10)
		draw_number[1] = ((((score % 10000) % 1000) % 100) / 10);
	if (score >= 100)
		draw_number[2] = ((((score % 10000) % 1000) / 100));
	if (score >= 1000)
		draw_number[3] = ((((score % 10000) / 1000)));
	if (score >= 10000)
		draw_number[4] = ((((score / 10000))));

}

// オブジェクトリスト確認
void InGameScene::ObjectListLoop(const float& delta_second)
{
	// 生成するオブジェクトリストの確認
	for (GameObject* obj : object_manager->GetObjects_Create())
	{
		// ボールの場合
		Ball* ball = dynamic_cast<Ball*>(obj);
		if (ball != nullptr)
		{
			screen_ball++;
			// レベルの設定
			ball->SetSpeedLevel(stage_level);

		}
	}

	// 破棄するオブジェクトリストの確認
	for (GameObject* obj : object_manager->GetObjects_Destroy())
	{
		// ボールの場合
		if (obj->GetCollision().object_type == eObjectType::eBall)
		{
			screen_ball--;
			
			// 画面内にボールがない場合
			if (screen_ball <= 0)
			{
				have_ball--;

				// ボールを持っていれば
				if(have_ball >= 0)
				{
					// プレイヤーがボールを生成する
					player->CreateBall();
					screen_ball = 1;
				}
			}
		}

		// ブロック1の場合
		if (dynamic_cast<Block*>(obj) != nullptr)
		{
			// 壊したマトのHPをスコアに加算する
			score += obj->GetHp();

			mato[0]++;
			screen_block1--;
			//ブロック1が無い場合
			if (screen_block1 == 0)
			{
				// ブロック1おかわり
				CreateBlock1();

				//レベルアップ
				stage_level++;
				for (GameObject* obj : scene_objects_list)
				{

					Ball* ball = dynamic_cast<Ball*>(obj);

					if (ball != nullptr)
					{
						ball->SetSpeedLevel(stage_level);
					}
				}
			}

		}


		// アイテムの場合
		if (obj->GetCollision().object_type == eObjectType::eItem)
		{
			// 取得したアイテムのカウント
			item++;
			// 500点加算
			score += 500;
		}

	}


	// 生成するオブジェクトの確認
	object_manager->CheckCreateObject();
	// 破棄するオブジェクトの確認
	object_manager->CheckDestroyObject();
	// 現在のオブジェクトリストを取得
	scene_objects_list = object_manager->GetObjectList();

	// リスト内のオブジェクトを更新する
	for (GameObject* obj : scene_objects_list)
	{
		obj->Update(delta_second);

		// オブジェクトマネージャーのインスタンス引き渡し
		if (obj->CheckInstance() == nullptr)
		{
			obj->SetInstance(object_manager);
		}

		// プレイヤー座標受け渡し
		obj->SetPlayerLocation(player->GetLocation());
		// プレイヤー加速度受け渡し
		obj->SetPlayerVelocity(player->GetVelocity());

	}


	//当たり判定チェック処理
	for (int a = 0; a < scene_objects_list.size(); a++)
	{
		for (int b = a + 1; b < scene_objects_list.size(); b++)
		{
			object_manager->HitCheck(scene_objects_list[a], scene_objects_list[b]);
			object_manager->HitCheck(scene_objects_list[b], scene_objects_list[a]);
		}
	}


	// 画面外へでたオブジェクトを破壊する
	for (GameObject* obj : scene_objects_list)
	{
		if (obj->GetLocation().x <= -50 || obj->GetLocation().x >= D_WIN_MAX_X - 230 + 50 ||
			obj->GetLocation().y <= -50 || obj->GetLocation().y >= D_WIN_MAX_Y + 50)
		{
			if(dynamic_cast<Block*>(obj) == nullptr)
			{
				obj->SetHp(0);
				object_manager->DestroyGameObject(obj);
			}
		}
	}
}

// ブロック1生成
void InGameScene::CreateBlock1()
{
	//ブロック生成 
	const int rows = 4;
	const int cols = 9;

	float startX = 80.0f;
	float startY = -300.0f;

	float blockWidth = 100.0f;
	float blockHeight = 50.0f;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			Vector2D pos(
				startX + x * (blockWidth + 10),
				startY + y * (blockHeight + 10)
			);

			GameObject* obj = object_manager->CreateGameObject<Block>(pos);
			obj->SetVelocity(Vector2D(0.0f, 1.0f));
			screen_block1++;
		}
	}
}