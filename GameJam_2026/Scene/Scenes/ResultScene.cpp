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

}

eSceneType ResultScene::GetNowSceneType()const
{
	return eSceneType::eResult;
}

void ResultScene::Animation(const float& delta_second)
{

}