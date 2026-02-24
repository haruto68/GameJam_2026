#include"HelpScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

HelpScene::HelpScene()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	background_makimono = rm->GetImages("Resource/Images/background_makimono.png")[0];
	background = rm->GetImages("Resource/Images/haikei.png")[0];
    controller = rm->GetImages("Resource/Images/controller_image.png")[0];
	a_botton = rm->GetImages("Resource/Images/button_a.png")[0];
	lb_image = rm->GetImages("Resource/Images/lb.png")[0];
	rb_image = rm->GetImages("Resource/Images/rb.png")[0];
	juuji = rm->GetImages("Resource/Images/dpad_juuji.png")[0];

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
	DrawRotaGraph(640, 360, 1.0, 0.0, background, true, false);
	DrawRotaGraphF(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2, 1.2, 0.0, background_makimono, true, FALSE);
	DrawBoxAA(220, 280, 310, 350, GetColor(0, 0, 0), TRUE);
	DrawBoxAA(220, 390, 310, 460, GetColor(0, 0, 0), TRUE);
	DrawBoxAA(220, 490, 310, 580, GetColor(0, 0, 0), TRUE);
	DrawRotaGraph(260, 200, 1.5, 0.0, a_botton, true, false);
	//DrawRotaGraph(400, 500, 7.0, 0.0, controller, true, false);
	DrawRotaGraph(265, 315, 1.5, 0.0, rb_image, true, false);
	DrawRotaGraph(265, 425, 1.5, 0.0, lb_image, true, false);
	DrawRotaGraph(265, 535, 1.5, 0.0, juuji, true, false);


	DrawFormatString(440, 182, GetColor(0, 0, 0), "・・・   決定");
	DrawFormatString(440, 287, GetColor(0, 0, 0), "・・・   右にはじく");
	DrawFormatString(440, 392, GetColor(0, 0, 0), "・・・   左にはじく");
	DrawFormatString(440, 497, GetColor(0, 0, 0), "・・・   左右に移動");

	
	

	if (botton == false)
		DrawRotaGraphF(1150, 650, 1.1, 0.0, botton_image[0], true, FALSE);
	else
		DrawRotaGraphF(1150, 650, 1.1, 0.0, botton_image[1], true, FALSE);
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