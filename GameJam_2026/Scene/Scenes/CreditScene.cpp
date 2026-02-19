#include"CreditScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

CreditScene::CreditScene()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
}

CreditScene::~CreditScene()
{

}

void CreditScene::Initialize()
{

}

eSceneType CreditScene::Update(const float& delta_second)
{

	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//入力情報の更新
	input->Update();

	//ゲームを終了
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		//return eSceneType::eExit;
	}

	// 決定
	if (input->GetButtonDown(XINPUT_BUTTON_A) || input->GetKeyDown(KEY_INPUT_E))
	{
		//return eSceneType::eTitle;
	}

	exit_time += delta_second;
	if (exit_time >= 5)
	{
		return eSceneType::eExit;
	}

	Animation(delta_second);

	return GetNowSceneType();
}

void CreditScene::Draw() const
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "クレジットシーン");
}

void CreditScene::Finalize()
{

}

eSceneType CreditScene::GetNowSceneType()const
{
	return eSceneType::eCreditScene;
}

void CreditScene::Animation(const float& delta_second)
{

}