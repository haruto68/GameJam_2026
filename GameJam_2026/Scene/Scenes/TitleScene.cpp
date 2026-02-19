#include"TitleScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

TitleScene::TitleScene() :
	cursor_num(0)
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
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
		if (cursor_num == 0)
		{
			return eSceneType::eInGame;
		}

		if (cursor_num == 1)
		{
			return  eSceneType::eHelp;
		}

		if (cursor_num == 2)
		{
			return  eSceneType::eRanking;
		}

		if (cursor_num == 3)
		{
			return  eSceneType::eExit;
		}
		//return eSceneType::eInGame;
	}

	// ヘルプシーンへ
	if (input->GetButtonDown(XINPUT_BUTTON_X) || input->GetKeyDown(KEY_INPUT_H))
	{
		//return eSceneType::eHelp;
	}
	

	Animation(delta_second);

	return GetNowSceneType();
}

//タイトルでのカーソル移動
void TitleScene::Draw() const
{
	if (cursor_num == 0)
	{
		//三角を横に表示
		DrawTriangle(1005, 520, 975, 500, 975, 540, GetColor(255, 0, 0), true);
		DrawFormatString(1000, 500, GetColor(255, 255, 255), "  スタート");
	}
	else
	{
		DrawFormatString(1000, 500, GetColor(255, 255, 255), "スタート");
	}


	if (cursor_num == 1)
	{
		//三角を横に表示
		DrawTriangle(1000, 570, 965, 550, 965, 590, GetColor(255, 0, 0), true);
		DrawFormatString(1000, 550, GetColor(255, 255, 255), "  説明");
	}
	else
	{
		DrawFormatString(1000, 550, GetColor(255, 255, 255), "説明");
	}

	if (cursor_num == 2)
	{
		//三角を横に表示
		DrawTriangle(1000, 620, 965, 600, 965, 640, GetColor(255, 0, 0), true);
		DrawFormatString(1000, 600, GetColor(255, 255, 255), " ランキング");
	}

	else
	{
		DrawFormatString(1000, 600, GetColor(255, 255, 255), "ランキング");
	}

	if (cursor_num == 3)
	{
		//三角を横に表示
		DrawTriangle(1000, 680, 965, 660, 965, 700, GetColor(255, 0, 0), true);
		DrawFormatString(1000, 650, GetColor(255, 255, 255), "  終了");
	}
	
	else
	{
		DrawFormatString(1000, 650, GetColor(255, 255, 255), " 終了");
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