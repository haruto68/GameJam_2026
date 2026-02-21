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
	player = object_manager->CreateGameObject<Player>(Vector2D(160, 360));

	//object_manager->CreateGameObject<Block>(Vector2D(160, 360));


	//ブロック生成 
	const int rows = 4;
	const int cols = 8;

	float startX = 100.0f;
	float startY = 100.0f;

	float blockWidth = 120.0f;
	float blockHeight = 30.0f;
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

	// ボール生成
	object_manager->CreateGameObject<Ball>(Vector2D(640, 360));
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

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	for (GameObject* obj : scene_objects_list)
	{
		obj->Draw(Vector2D(0, 0), true);
	}
	
	DrawFormatString(1080, 300, GetColor(255, 255, 255), "スコア", score);
	DrawFormatString(1080, 350, GetColor(255, 255, 255), "%d", score);
}

void InGameScene::Finalize()
{
	////スコアランダム
	//score = rand() % 10000;
	//item = 3;
	//mato[0] = 8;
	//mato[1] = 4;
	//mato[2] = 1;

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
	// 破棄するオブジェクトリストの確認
	for (GameObject* obj : object_manager->GetObjects_Destroy())
	{
		// 壊したマトのHPをスコアに加算する
		if (obj->GetCollision().object_type == eObjectType::eBlock)
		{
			// スコア加算
			score += obj->GetHp();

			// マト1のカウント
			if (obj->GetHp() == 500)
			{
				mato[0]++;
			}

		}

		// 取得したアイテムのカウント
		if (obj->GetCollision().object_type == eObjectType::eItem)
		{
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
}