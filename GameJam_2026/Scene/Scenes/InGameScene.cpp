#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include"../../Objects/GameObjectManager.h"
#include <Windows.h>
#include<time.h>

InGameScene::InGameScene():
	object_manager(nullptr),
	player()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	srand(time(NULL));

	//GameObjectManagerインスタンス取得
	object_manager = new GameObjectManager();

	//プレイヤー生成
	player = object_manager->CreateGameObject<Player>(Vector2D(0, 0));

	//ブロック生成 
	const int rows = 4;
	const int cols = 9;

	float startX = 80.0f;
	float startY = 100.0f;

	float blockWidth = 100.0f;
	float blockHeight = 50.0f;
	//Vector2D pos = 0;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			Vector2D pos(
				startX + x * (blockWidth + 10),
				startY + y * (blockHeight + 10)
			);
			/*pos.x = startX + x * (blockWidth + 10);
			pos.y = startY + y * (blockHeight + 10);*/
			
			
			object_manager->CreateGameObject<Block>(pos);
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
	int n = 0;
	for (GameObject* obj : scene_objects_list)
	{
		obj->Draw(Vector2D(0, 0), true);
		n++;
	}
	DrawBox(1051, 0, D_WIN_MAX_X, D_WIN_MAX_Y, 0x000000, true);

	DrawFormatString(1080, 350, GetColor(255, 255, 255), "手裏剣数");
	DrawFormatString(1080, 400, GetColor(255, 255, 255), "画面内");
	DrawFormatString(1080, 450, GetColor(255, 255, 255), "  %d", screen_ball);
	DrawFormatString(1080, 500, GetColor(255, 255, 255), "所持中");
	DrawFormatString(1080, 550, GetColor(255, 255, 255), "  %d", have_ball);
	
	DrawFormatString(1080, 250, GetColor(255, 255, 255), "スコア");
	DrawFormatString(1080, 300, GetColor(255, 255, 255), "%d", score);


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
}

eSceneType InGameScene::GetNowSceneType()const
{
	return eSceneType::eInGame;
}

void InGameScene::Animation(const float& delta_second)
{

}

// オブジェクトリスト確認
void InGameScene::ObjectListLoop(const float& delta_second)
{
	// 生成するオブジェクトリストの確認
	for (GameObject* obj : object_manager->GetObjects_Create())
	{
		// ボールの場合
		if (obj->GetCollision().object_type == eObjectType::eBall)
		{
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

		// ブロックの場合
		if (obj->GetCollision().object_type == eObjectType::eBlock)
		{
			// 壊したマトのHPをスコアに加算する
			score += obj->GetHp();

			// マト1のカウント
			if (obj->GetHp() == 500)
			{
				mato[0]++;
			}
		}

		// アイテムの場合
		if (obj->GetCollision().object_type == eObjectType::eItem)
		{
			// 取得したアイテムのカウント
			item++;
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
			obj->SetHp(0);
			object_manager->DestroyGameObject(obj);
		}
	}
}