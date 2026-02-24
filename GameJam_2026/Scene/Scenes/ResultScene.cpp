#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

ResultScene::ResultScene():Result_handle(0)
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
	background_makimono = rm->GetImages("Resource/Images/background_makimono.png")[0];
	mato1_image = rm->GetImages("Resource/Images/mato1.png")[0];
	mato2_image = rm->GetImages("Resource/Images/maruta1.png")[0];
	item_image = rm->GetImages("Resource/Images/makimono1.png")[0];

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
	Result_handle = LoadSoundMem("Resource/sound/Results.mp3");
	ChangeVolumeSoundMem(200, Result_handle);
	if (Result_handle != -1)
	{
		PlaySoundMem(Result_handle, DX_PLAYTYPE_LOOP);
	}

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

	mato1_score = mato[0] * 500;
	mato2_score = mato[1] * 1000;
	item_score = item * 2000;

	score = mato1_score + mato2_score + item_score;

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

	DrawRotaGraphF(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2, 1.2, 0.0, background_makimono, true, FALSE);

	int x = 130;
	int y = 200;
	int f = 50;
	DrawFormatString(220,600, 0x000000, "ハイスコア");
	DrawFormatString(y, x + f * 0, 0x000000, "マト1");
	DrawFormatString(y, x + f * 1, 0x000000, "マト2");
	DrawFormatString(y, x + f * 2, 0x000000, "アイテム");
	
	SetFontSize(68);
	DrawFormatString(200,425, 0x000000, "スコア");
	SetFontSize(48);
	
	DrawRotaGraphF(420, 250, 0.2, 0.0, item_image, true, FALSE);
	DrawRotaGraphF(345, 205, 0.2, 0.0, mato1_image, true, FALSE);
	DrawRotaGraphF(345, 155, 0.2, 0.0, mato2_image, true, FALSE);
	

	y = 650;

	DrawFormatString(550,600 , 0x000000, "%d", ranking[0]);
	DrawFormatString(y, x + f * 0, 0x000000, "%d × 500 =  %d", mato[0],mato1_score);
	DrawFormatString(y, x + f * 1, 0x000000, "%d × 1000 =  %d", mato[1], mato2_score);
	DrawFormatString(y, x + f * 2, 0x000000, "%d × 2000 =  %d", item, item_score);
	SetFontSize(68);
	DrawFormatString(480,430 , 0x000000, "%d", score);
	SetFontSize(48);


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


		if (Result_handle != -1)
		{
			StopSoundMem(Result_handle);
			DeleteSoundMem(Result_handle);
		}

	}



	
}

eSceneType ResultScene::GetNowSceneType()const
{
	return eSceneType::eResult;
}

void ResultScene::Animation(const float& delta_second)
{

}