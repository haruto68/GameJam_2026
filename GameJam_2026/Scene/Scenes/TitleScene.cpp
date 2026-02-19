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
		return eSceneType::eInGame;
	}

	// ヘルプシーンへ
	if (input->GetButtonDown(XINPUT_BUTTON_X) || input->GetKeyDown(KEY_INPUT_H))
	{
		return eSceneType::eHelp;
	}

	Animation(delta_second);

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "タイトルシーン");
	DrawFormatString(0, 200, GetColor(255, 255, 255), "%d",cursor_num);
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