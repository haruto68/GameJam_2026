#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

ResultScene::ResultScene()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	FILE* fp;		// ファイルパス
	errno_t result;	// ファイル読込み結果

	//ランキングファイルオープン
	fp = nullptr;
	result = fopen_s(&fp, "Resource/save/ranking_data.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("Resoure/save/ranking_data.csvが読み込めません\n");
	}

	//ランキング
	for (int i = 0; i < 5; i++)
	{
		fscanf_s(fp, "%6d,\n,\n,\n", &ranking[i]);
	}

	//ファイルクローズ
	fclose(fp);


	//リザルトファイルオープン
	fp = nullptr;
	result = fopen_s(&fp, "Resource/save/result_data.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("Resoure/save/result_data.csvが読み込めません\n");
	}

	//スコア
	fscanf_s(fp, "%6d,\n", &score);

	//アイテム
	fscanf_s(fp, "%6d,\n", &item);

	//マト
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(fp, "%6d,\n", &mato[i]);
	}

	//ファイルクローズ
	fclose(fp);
}

eSceneType ResultScene::Update(const float& delta_second)
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

	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT) || input->GetKeyDown(KEY_INPUT_D))
	{
		if (cursor_num < 2 - 1)
		{
			cursor_num += 1;
		}
	}
	// カーソル下移動
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT) || input->GetKeyDown(KEY_INPUT_A))
	{
		if (cursor_num > 0)
			cursor_num -= 1;
		
	}

	// 決定
	if (input->GetButtonDown(XINPUT_BUTTON_A) || input->GetKeyDown(KEY_INPUT_E))
	{
		if (cursor_num == 0)
		{
			return eSceneType::eInGame;
		}


		if (cursor_num == 1)
		{
			return eSceneType::eTitle;
		}
		//return eSceneType::eTitle;
	}

	

	Animation(delta_second);

	return GetNowSceneType();
}

void ResultScene::Draw() const
{
	int f = 50;
	DrawFormatString(440, f * 0, 0xffffff, "ハイスコア");
	DrawFormatString(440, f * 1, 0xffffff, "ロースコア");
	DrawFormatString(440, f * 3, 0xffffff, "スコア");
	DrawFormatString(440, f * 4, 0xffffff, "アイテム");
	DrawFormatString(440, f * 5, 0xffffff, "マト1");
	DrawFormatString(440, f * 6, 0xffffff, "マト2");
	DrawFormatString(440, f * 7, 0xffffff, "マト3");

	DrawFormatString(840, f * 0, 0xffffff, "%d", ranking[0]);
	DrawFormatString(840, f * 1, 0xffffff, "%d", ranking[4]);
	DrawFormatString(840, f * 3, 0xffffff, "%d", score);
	DrawFormatString(840, f * 4, 0xffffff, "%d", item);
	DrawFormatString(840, f * 5, 0xffffff, "%d", mato[0]);
	DrawFormatString(840, f * 6, 0xffffff, "%d", mato[1]);
	DrawFormatString(840, f * 7, 0xffffff, "%d", mato[2]);



	if (cursor_num == 0)
	{
		DrawTriangle(150, 625, 120, 600, 120, 650, GetColor(255, 0, 0), true);
		DrawFormatString(160, 600, GetColor(255, 255, 255), " リスタート");
	}
	else
	{
		DrawFormatString(160, 600, GetColor(255, 255, 255), "リスタート");
	}

	if (cursor_num == 1)
	{
		DrawTriangle(900, 625, 870, 600, 870, 650, GetColor(255, 0, 0), true);
		DrawFormatString(900, 600, GetColor(255, 255, 255), " タイトル");
	}
	else
	{
		DrawFormatString(900, 600, GetColor(255, 255, 255), "タイトル");
	}
	
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", cursor_num);
}

void ResultScene::Finalize()
{
	int kari = 0;

	//ランキング更新
	if (score > ranking[4])
	{
		ranking[4] = score;
		//ランキングソート
		for (int i = 4; i > 0; i--)
		{
			if (ranking[i] > ranking[i - 1])
			{
				kari = ranking[i - 1];
				ranking[i - 1] = ranking[i];
				ranking[i] = kari;
			}
		}


		//ランキングデータの書き込み
		FILE* fp = nullptr;
		//ファイルオープン
		errno_t result = fopen_s(&fp, "Resource/save/ranking_data.csv", "w");

		//エラーチェック
		if (result != 0)
		{
			throw("Resource/save/ranking_data.csvが開けません\n");
		}

		//ランキングを保存
		for (int i = 0; i < 5; i++)
		{
			fprintf(fp, "%d,\n", ranking[i]);
		}

		//ファイルクローズ
		fclose(fp);

	}



	
}

eSceneType ResultScene::GetNowSceneType()const
{
	return eSceneType::eResult;
}

void ResultScene::Animation(const float& delta_second)
{

}