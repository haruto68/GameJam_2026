#include"CreditScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

CreditScene::CreditScene()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	background_makimono = rm->GetImages("Resource/Images/background_makimono.png")[0];

	background = rm->GetImages("Resource/Images/haikei.png")[0];
	
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
	DrawRotaGraph(640, 360, 1.0, 0.0, background, true, false);
	DrawRotaGraphF(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2, 1.2, 0.0, background_makimono, true, FALSE);
	DrawFormatString(240, 200, GetColor(100, 0, 0), "イラストレーター　　島 維那");
	DrawFormatString(240, 250, GetColor(100, 0, 0), "　　　　　　　　　　大城 新奈");
	DrawFormatString(240, 400, GetColor(0, 100, 0), "プログラマー　　大城 悠仁");
	DrawFormatString(630, 450, GetColor(0, 100, 0), "幸地 秀斗");
	DrawFormatString(630, 500, GetColor(0, 100, 0), "新城 怜空");
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