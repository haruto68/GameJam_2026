#include"HelpScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

HelpScene::HelpScene()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	botton_image[0] = rm->GetImages("Resource/Images/modoru1.png")[0];
	botton_image[1] = rm->GetImages("Resource/Images/modoru2.png")[0];
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
	if (input->GetButtonDown(XINPUT_BUTTON_A) || input->GetKeyDown(KEY_INPUT_E))
	{
		botton = true;
	}

	if(botton == true)
	{
		botton_time += delta_second;
		if (botton_time >= 0.5)
		{
			return eSceneType::eTitle;
		}
	}
	

	Animation(delta_second);

	return GetNowSceneType();
}

void HelpScene::Draw() const
{
	if (botton == false)
	{
		DrawRotaGraphF(1150, 650, 1.1, 0.0, botton_image[0], true, FALSE);
	}

	else
	{
		DrawRotaGraphF(1150, 650, 1.1, 0.0, botton_image[1], true, FALSE);
	}
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "ヘルプシーン");
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