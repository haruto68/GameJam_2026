#include"TitleScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

TitleScene::TitleScene() :
	cursor_num(0)
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	botton_image[0][0] = rm->GetImages("Resource/Images/hajime1.png")[0];
	botton_image[0][1] = rm->GetImages("Resource/Images/hajime2.png")[0];
	botton_image[1][0] = rm->GetImages("Resource/Images/setumei1.png")[0];
	botton_image[1][1] = rm->GetImages("Resource/Images/setumei2.png")[0];
	botton_image[2][0] = rm->GetImages("Resource/Images/juni1.png")[0];
	botton_image[2][1] = rm->GetImages("Resource/Images/juni2.png")[0];
	botton_image[3][0] = rm->GetImages("Resource/Images/syuryou1.png")[0];
	botton_image[3][1] = rm->GetImages("Resource/Images/syuryou2.png")[0];
}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	
}

eSceneType TitleScene::Update(const float& delta_second)
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

	// カーソル上移動
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_UP) || input->GetKeyDown(KEY_INPUT_W))
	{
		if (cursor_num > 0)
			cursor_num -= 1;
	}
	// カーソル下移動
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN) || input->GetKeyDown(KEY_INPUT_S))
	{
		if (cursor_num < CURSOR_NUMS - 1)
			cursor_num += 1;
	}

	// カーソル決定
	if (input->GetButtonDown(XINPUT_BUTTON_A) || input->GetKeyDown(KEY_INPUT_E))
	{
		botton = true;
		
		//return eSceneType::eInGame;
	}

	if (botton == true)
	{
		botton_time += delta_second;

		if (cursor_num == 0)
		{

			if (botton_time >= 0.5)
			{
				return eSceneType::eInGame;
			}
		}

		if (cursor_num == 1)
		{
			if (botton_time >= 0.5)
			{
				return  eSceneType::eHelp;
			}
		}

		if (cursor_num == 2)
		{
			if (botton_time >= 0.5)
			{
				return  eSceneType::eRanking;
			}
		}

		if (cursor_num == 3)
		{
			if (botton_time >= 0.5)
			{
				return  eSceneType::eCreditScene;
			}
		}
	}

	

	Animation(delta_second);

	return GetNowSceneType();
}

//タイトルでのカーソル移動
void TitleScene::Draw() const
{
	if(botton == false)
	{
		if (cursor_num == 0)
		{
			//三角を横に表示
			//DrawTriangle(1005, 520, 975, 500, 975, 540, GetColor(255, 0, 0), true);
			DrawRotaGraphF(1100, 350, 1.1, 0.0, botton_image[0][0], true, FALSE);
			//DrawFormatString(1000, 500, GetColor(255, 255, 255), "  スタート");
		}
		else
		{
			DrawRotaGraphF(1150, 350, 1.1, 0.0, botton_image[0][0], true, FALSE);
			//DrawFormatString(1000, 500, GetColor(255, 255, 255), "スタート");
		}



		if (cursor_num == 1)
		{
			//三角を横に表示
			//DrawTriangle(1000, 570, 965, 550, 965, 590, GetColor(255, 0, 0), true);
			//DrawFormatString(1000, 550, GetColor(255, 255, 255), "  説明");
			DrawRotaGraphF(1100, 450, 1.1, 0.0, botton_image[1][0], true, FALSE);
		}
		else
		{
			DrawRotaGraphF(1150, 450, 1.1, 0.0, botton_image[1][0], true, FALSE);
			//DrawFormatString(1000, 550, GetColor(255, 255, 255), "説明");
		}

		if (cursor_num == 2)
		{
			//三角を横に表示
			//DrawTriangle(1000, 620, 965, 600, 965, 640, GetColor(255, 0, 0), true);
			//DrawFormatString(1000, 600, GetColor(255, 255, 255), " ランキング");
			DrawRotaGraphF(1100, 550, 1.1, 0.0, botton_image[2][0], true, FALSE);
		}

		else
		{
			DrawRotaGraphF(1150, 550, 1.1, 0.0, botton_image[2][0], true, FALSE);
			//DrawFormatString(1000, 600, GetColor(255, 255, 255), "ランキング");
		}

		if (cursor_num == 3)
		{
			//三角を横に表示
			//DrawTriangle(1000, 680, 965, 660, 965, 700, GetColor(255, 0, 0), true);
			//DrawFormatString(1000, 650, GetColor(255, 255, 255), "  終了");
			DrawRotaGraphF(1100, 650, 1.1, 0.0, botton_image[3][0], true, FALSE);
		}

		else
		{
			DrawRotaGraphF(1150, 650, 1.1, 0.0, botton_image[3][0], true, FALSE);
			//DrawFormatString(1000, 650, GetColor(255, 255, 255), " 終了");
		}
	}

	if (botton == true)
	{
		if (cursor_num == 0)
		{
			DrawRotaGraphF(1100, 350, 1.1, 0.0, botton_image[0][1], true, FALSE);
		}
		else
		{
			DrawRotaGraphF(1150, 350, 1.1, 0.0, botton_image[0][0], true, FALSE);
		}

		if (cursor_num == 1)
		{
				DrawRotaGraphF(1100, 450, 1.1, 0.0, botton_image[1][1], true, FALSE);
		}
		else
		{
			DrawRotaGraphF(1150, 450, 1.1, 0.0, botton_image[1][0], true, FALSE);
		}

		if (cursor_num == 2)
		{
				DrawRotaGraphF(1100, 550, 1.1, 0.0, botton_image[2][1], true, FALSE);
		}
		else
		{
			DrawRotaGraphF(1150, 550, 1.1, 0.0, botton_image[2][0], true, FALSE);
		}

		if (cursor_num == 3)
		{
				DrawRotaGraphF(1100, 650, 1.1, 0.0, botton_image[3][1], true, FALSE);
		}
		else
		{
			DrawRotaGraphF(1150, 650, 1.1, 0.0, botton_image[3][0], true, FALSE);
		}
	}
}


void TitleScene::Finalize()
{
	
}

eSceneType TitleScene::GetNowSceneType()const
{
	return eSceneType::eTitle;
}

void TitleScene::Animation(const float& delta_second)
{
	
}