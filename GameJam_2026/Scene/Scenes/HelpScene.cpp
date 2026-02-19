#include"HelpScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

HelpScene::HelpScene()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
}

HelpScene::~HelpScene()
{

}

void HelpScene::Initialize()
{

}

eSceneType HelpScene::Update(const float& delta_second)
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

	// タイトルシーンへ戻る
	if (input->GetButtonDown(XINPUT_BUTTON_X) || input->GetKeyDown(KEY_INPUT_H))
	{
		return eSceneType::eTitle;
	}

	Animation(delta_second);

	return GetNowSceneType();
}

void HelpScene::Draw() const
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ヘルプシーン");
}

void HelpScene::Finalize()
{

}

eSceneType HelpScene::GetNowSceneType()const
{
	return eSceneType::eHelp;
}

void HelpScene::Animation(const float& delta_second)
{

}