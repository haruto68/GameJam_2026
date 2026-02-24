#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

ResultScene::ResultScene():Result_handle(0)
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
	//数字
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

	background_makimono = rm->GetImages("Resource/Images/background_makimono.png")[0];
	mato1_image = rm->GetImages("Resource/Images/mato1.png")[0];
	mato2_image = rm->GetImages("Resource/Images/maruta1.png")[0];
	item_image = rm->GetImages("Resource/Images/makimono1.png")[0];
	kakeru_image = rm->GetImages("Resource/Images/kakeru.png")[0];
	ikoru_image = rm->GetImages("Resource/Images/ikoru.png")[0];
	score_image = rm->GetImages("Resource/Images/score.png")[0];
	highscore_image = rm->GetImages("Resource/Images/highscore.png")[0];

	background = rm->GetImages("Resource/Images/haikei.png")[0];
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

	mato1_score = mato[0] * 100;
	mato2_score = mato[1] * 300;
	item_score = item * 500;

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
	DrawRotaGraph(640, 360, 1.0, 0.0, background, true, false);

	DrawRotaGraphF(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2, 1.2, 0.0, background_makimono, true, FALSE);

	int x = 130;
	int y = 200;
	int f = 50;

	DrawRotaGraphF(320, 620, 1.2, 0.0, highscore_image, true, false);
	
	
	DrawRotaGraphF(310, 460, 1.3, 0.0, score_image, true, false);

	DrawRotaGraphF(250, 150, 0.4, 0.0, mato2_image, true, FALSE);
	DrawRotaGraphF(250, 200, 0.25, 0.0, mato1_image, true, FALSE);
	DrawRotaGraphF(250, 250, 0.25, 0.0, item_image, true, FALSE);
	
	

	y = 650;

	DrawRotaGraphF(710, 150, 0.2, 0.0, numbers_image[0], true, false);
	DrawRotaGraphF(675, 150, 0.2, 0.0, numbers_image[0], true, false);
	DrawRotaGraphF(635, 150, 0.2, 0.0, numbers_image[1], true, false);
	DrawRotaGraphF(710, 250, 0.2, 0.0, numbers_image[0], true, false);
	DrawRotaGraphF(675, 250, 0.2, 0.0, numbers_image[0], true, false);
	DrawRotaGraphF(635, 250, 0.2, 0.0, numbers_image[5], true, false);
	DrawRotaGraphF(710, 200, 0.2, 0.0, numbers_image[0], true, false);
	DrawRotaGraphF(675, 200, 0.2, 0.0, numbers_image[0], true, false);
	DrawRotaGraphF(635, 200, 0.2, 0.0, numbers_image[3], true, false);

	//ハイスコア
	DrawRotaGraphF(750, 622, 0.2, 0.0, numbers_image[draw_number[0]], true, false);
	DrawRotaGraphF(700, 622, 0.2, 0.0, numbers_image[draw_number[1]], true, false);
	DrawRotaGraphF(650, 622, 0.2, 0.0, numbers_image[draw_number[2]], true, false);
	DrawRotaGraphF(600, 622, 0.2, 0.0, numbers_image[draw_number[3]], true, false);
	DrawRotaGraphF(550, 622, 0.2, 0.0, numbers_image[draw_number[4]], true, false);
	
	//スコア
	DrawRotaGraphF(750, 455, 0.3, 0.0, numbers_image[draw_number2[0]], true, false);
	DrawRotaGraphF(700, 455, 0.3, 0.0, numbers_image[draw_number2[1]], true, false);
	DrawRotaGraphF(650, 455, 0.3, 0.0, numbers_image[draw_number2[2]], true, false);
	DrawRotaGraphF(600, 455, 0.3, 0.0, numbers_image[draw_number2[3]], true, false);
	DrawRotaGraphF(550, 455, 0.3, 0.0, numbers_image[draw_number2[4]], true, false);

	//まと1スコア
	DrawRotaGraphF(1030, 150, 0.2, 0.0, numbers_image[draw_number3[0]], true, false);
	DrawRotaGraphF(990, 150, 0.2, 0.0, numbers_image[draw_number3[1]], true, false);
	DrawRotaGraphF(950, 150, 0.2, 0.0, numbers_image[draw_number3[2]], true, false);
	DrawRotaGraphF(910, 150, 0.2, 0.0, numbers_image[draw_number3[3]], true, false);
	DrawRotaGraphF(880, 150, 0.2, 0.0, numbers_image[draw_number3[4]], true, false);

	//まと2スコア
	DrawRotaGraphF(1030, 200, 0.2, 0.0, numbers_image[draw_number4[0]], true, false);
	DrawRotaGraphF(990, 200, 0.2, 0.0, numbers_image[draw_number4[1]], true, false);
	DrawRotaGraphF(950, 200, 0.2, 0.0, numbers_image[draw_number4[2]], true, false);
	DrawRotaGraphF(910, 200, 0.2, 0.0, numbers_image[draw_number4[3]], true, false);
	DrawRotaGraphF(880, 200, 0.2, 0.0, numbers_image[draw_number4[4]], true, false);


	//アイテムスコア
	DrawRotaGraphF(1030, 250, 0.2, 0.0, numbers_image[draw_number5[0]], true, false);
	DrawRotaGraphF(990, 250, 0.2, 0.0, numbers_image[draw_number5[1]], true, false);
	DrawRotaGraphF(950, 250, 0.2, 0.0, numbers_image[draw_number5[2]], true, false);
	DrawRotaGraphF(910, 250, 0.2, 0.0, numbers_image[draw_number5[3]], true, false);
	DrawRotaGraphF(880, 250, 0.2, 0.0, numbers_image[draw_number5[4]], true, false);

	//まと1の数
	DrawRotaGraphF(440, 150, 0.2, 0.0, numbers_image[draw_number6[0]], true, false);
	DrawRotaGraphF(400, 150, 0.2, 0.0, numbers_image[draw_number6[1]], true, false);
	DrawRotaGraphF(360, 150, 0.2, 0.0, numbers_image[draw_number6[2]], true, false);
	DrawRotaGraphF(320, 150, 0.2, 0.0, numbers_image[draw_number6[3]], true, false);
	DrawRotaGraphF(280, 150, 0.2, 0.0, numbers_image[draw_number6[4]], true, false);


	//まと2の数
	DrawRotaGraphF(440, 200, 0.2, 0.0, numbers_image[draw_number7[0]], true, false);
	DrawRotaGraphF(400, 200, 0.2, 0.0, numbers_image[draw_number7[1]], true, false);
	DrawRotaGraphF(360, 200, 0.2, 0.0, numbers_image[draw_number7[2]], true, false);
	DrawRotaGraphF(320, 200, 0.2, 0.0, numbers_image[draw_number7[3]], true, false);
	DrawRotaGraphF(280, 200, 0.2, 0.0, numbers_image[draw_number7[4]], true, false);


	//アイテムの数
	DrawRotaGraphF(440, 250, 0.2, 0.0, numbers_image[draw_number8[0]], true, false);
	DrawRotaGraphF(400, 250, 0.2, 0.0, numbers_image[draw_number8[1]], true, false);
	DrawRotaGraphF(360, 250, 0.2, 0.0, numbers_image[draw_number8[2]], true, false);
	DrawRotaGraphF(320, 250, 0.2, 0.0, numbers_image[draw_number8[3]], true, false);
	DrawRotaGraphF(280, 250, 0.2, 0.0, numbers_image[draw_number8[4]], true, false);






	//DrawFormatString(550,600 , 0x000000, "%d", ranking[0]);
	//DrawFormatString(y, x + f * 0, 0x000000, "  ×        =  ");
	//DrawFormatString(y, x + f * 1, 0x000000, "  ×        =  ");
	//DrawFormatString(y, x + f * 2, 0x000000, "  ×        =  ");
	//SetFontSize(68);
	DrawRotaGraphF(560, 150, 1.0, 0.0, kakeru_image, true, false);
	DrawRotaGraphF(560, 200, 1.0, 0.0, kakeru_image, true, false);
	DrawRotaGraphF(560, 250, 1.0, 0.0, kakeru_image, true, false);

	DrawRotaGraphF(800, 150, 1.0, 0.0, ikoru_image, true, false);
	DrawRotaGraphF(800, 200, 1.0, 0.0, ikoru_image, true, false);
	DrawRotaGraphF(800, 250, 1.0, 0.0, ikoru_image, true, false);




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
	//ハイスコア
	draw_number[0] = ((((ranking[0] % 10000) % 1000) % 100) % 10);

	if (ranking[0] >= 10)
	{
		draw_number[1] = ((((ranking[0] % 10000) % 1000) % 100) / 10);
	}
	if (ranking[0] >= 100)
	{
		draw_number[2] = ((((ranking[0] % 10000) % 1000) / 100));
	}
	if (ranking[0] >= 1000)
	{
		draw_number[3] = ((((ranking[0] % 10000) / 1000)));
	}
	if (ranking[0] >= 10000)
	{
		draw_number[4] = ((((ranking[0] / 10000))));
	}


	//スコア
	draw_number2[0] = ((((score % 10000) % 1000) % 100) % 10);

	if (score >= 10)
	{
		draw_number2[1] = ((((score % 10000) % 1000) % 100) / 10);
	}
	if (score >= 100)
	{
		draw_number2[2] = ((((score % 10000) % 1000) / 100));
	}
	if (score >= 1000)
	{
		draw_number2[3] = ((((score % 10000) / 1000)));
	}
	if (score >= 10000)
	{
		draw_number2[4] = ((((score / 10000))));
	}


	//まと1スコア
	draw_number3[0] = ((((mato[0] * 100 % 10000) % 1000) % 100) % 10);

	if (mato[0] * 100 >= 10)
	{
		draw_number3[1] = ((((mato[0] * 100 % 10000) % 1000) % 100) / 10);
	}
	if (mato[0] * 100 >= 100)
	{
		draw_number3[2] = ((((mato[0] * 100 % 10000) % 1000) / 100));
	}
	if (mato[0] * 100 >= 1000)
	{
		draw_number3[3] = ((((mato[0] * 100 % 10000) / 1000)));
	}
	if (mato[0] * 100 >= 10000)
	{
		draw_number3[4] = ((((mato[0] * 100 / 10000))));
	}


	//まと2スコア
	draw_number4[0] = ((((mato[1]*300 % 10000) % 1000) % 100) % 10);

	if (mato[1] * 300 >= 10)
	{
		draw_number4[1] = ((((mato[1] * 300 % 10000) % 1000) % 100) / 10);
	}
	if (mato[1] * 300 >= 100)
	{
		draw_number4[2] = ((((mato[1] * 300 % 10000) % 1000) / 100));
	}
	if (mato[1] * 300 >= 1000)
	{
		draw_number4[3] = ((((mato[1] * 300 % 10000) / 1000)));
	}
	if (mato[1] * 300 >= 10000)
	{
		draw_number4[4] = ((((mato[1] * 300 / 10000))));
	}


	//アイテムスコア
	draw_number5[0] = ((((item * 500 % 10000) % 1000) % 100) % 10);

	if (item * 500 >= 10)
	{
		draw_number5[1] = ((((item * 500 % 10000) % 1000) % 100) / 10);
	}
	if (item * 500 >= 100)
	{
		draw_number5[2] = ((((item * 500 % 10000) % 1000) / 100));
	}
	if (item * 500 >= 1000)
	{
		draw_number5[3] = ((((item * 500 % 10000) / 1000)));
	}
	if (item * 500 >= 10000)
	{
		draw_number5[4] = ((((item * 500 / 10000))));
	}


	//まと1の数
	draw_number6[0] = ((((mato[0] % 10000) % 1000) % 100) % 10);

	if (mato[0] >= 10)
	{
		draw_number6[1] = ((((mato[0] % 10000) % 1000) % 100) / 10);
	}
	if (mato[0] >= 100)
	{
		draw_number6[2] = ((((mato[0] % 10000) % 1000) / 100));
	}
	if (mato[0] >= 1000)
	{
		draw_number6[3] = ((((mato[0] % 10000) / 1000)));
	}
	if (mato[0] >= 10000)
	{
		draw_number6[4] = ((((mato[0] / 10000))));
	}



	//まと2の数
	draw_number7[0] = ((((mato[1] % 10000) % 1000) % 100) % 10);

	if (mato[1] >= 10)
	{
		draw_number7[1] = ((((mato[1] % 10000) % 1000) % 100) / 10);
	}
	if (mato[1] >= 100)
	{
		draw_number7[2] = ((((mato[1] % 10000) % 1000) / 100));
	}
	if (mato[1] >= 1000)
	{
		draw_number7[3] = ((((mato[1] % 10000) / 1000)));
	}
	if (mato[1] >= 10000)
	{
		draw_number7[4] = ((((mato[1] / 10000))));
	}


	//アイテムの数
	draw_number8[0] = ((((item % 10000) % 1000) % 100) % 10);

	if (item >= 10)
	{
		draw_number8[1] = ((((item % 10000) % 1000) % 100) / 10);
	}
	if (item >= 100)
	{
		draw_number8[2] = ((((item % 10000) % 1000) / 100));
	}
	if (item >= 1000)
	{
		draw_number8[3] = ((((item % 10000) / 1000)));
	}
	if (item >= 10000)
	{
		draw_number8[4] = ((((item / 10000))));
	}
}