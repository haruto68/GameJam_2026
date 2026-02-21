#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

ResultScene::ResultScene()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	botton_image[0][0] = rm->GetImages("Resource/Images/saityousen1.png")[0];
	botton_image[0][1] = rm->GetImages("Resource/Images/saityousen2.png")[0];
	botton_image[1][0] = rm->GetImages("Resource/Images/modoru1.png")[0];
	botton_image[1][1] = rm->GetImages("Resource/Images/modoru2.png")[0];
	botton_image[2][0] = rm->GetImages("Resource/Images/juni1.png")[0];
	botton_image[2][1] = rm->GetImages("Resource/Images/juni2.png")[0];
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

	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_UP) || input->GetKeyDown(KEY_INPUT_W))
	{
		if (cursor_num > 0)
			cursor_num -= 1;
	}
	// カーソル下移動
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN) || input->GetKeyDown(KEY_INPUT_S))
	{
		if (cursor_num < 3 - 1)
			cursor_num += 1;
	}

	// 決定
	if (input->GetButtonDown(XINPUT_BUTTON_A) || input->GetKeyDown(KEY_INPUT_E))
	{
		botton = true;
		//return eSceneType::eTitle;
	}

	

	if (botton == true)
	{
		botton_time += delta_second;
		if (cursor_num == 0)
		{
			if(botton_time >= 0.5)
			{
				return eSceneType::eInGame;
			}
		}

		if (cursor_num == 1)
		{
			if (botton_time >= 0.5)
			{
				return eSceneType::eRanking;
			}
		}

		if (cursor_num == 2)
		{
			if (botton_time >= 0.5)
			{
				return eSceneType::eTitle;
			}
		}
		
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


	if(botton == false)
	{
		if (cursor_num == 0)
		{
			DrawRotaGraphF(1050, 450, 1.1, 0.0, botton_image[0][0], true, FALSE);
		}
		else
		{
			DrawRotaGraphF(1100, 450, 1.1, 0.0, botton_image[0][0], true, FALSE);
		}

		if (cursor_num == 1)
		{
			DrawRotaGraphF(1050, 550, 1.1, 0.0, botton_image[2][0], true, FALSE);
		}
		else
		{
			DrawRotaGraphF(1100, 550, 1.1, 0.0, botton_image[2][0], true, FALSE);
		}

		if (cursor_num == 2)
		{
			DrawRotaGraphF(1050, 650, 1.1, 0.0, botton_image[1][0], true, FALSE);
		}
		else
		{
			DrawRotaGraphF(1100, 650, 1.1, 0.0, botton_image[1][0], true, FALSE);
		}

		
	}

	if (botton == true)
	{
		if (cursor_num == 0)
		{
			DrawRotaGraphF(1050, 450, 1.1, 0.0, botton_image[0][1], true, FALSE);
		}
		else
		{
			DrawRotaGraphF(1100, 450, 1.1, 0.0, botton_image[0][0], true, FALSE);
		}

		if (cursor_num == 1)
		{
			DrawRotaGraphF(1050, 550, 1.1, 0.0, botton_image[2][1], true, FALSE);
		}
		else
		{
			DrawRotaGraphF(1100, 550, 1.1, 0.0, botton_image[2][0], true, FALSE);
		}

		if (cursor_num == 2)
		{
			DrawRotaGraphF(1050, 650, 1.1, 0.0, botton_image[1][1], true, FALSE);
		}
		else
		{
			DrawRotaGraphF(1100, 650, 1.1, 0.0, botton_image[1][0], true, FALSE);
		}

		
	}
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