#include"RankingScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

RankingScene::RankingScene()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
}

RankingScene::~RankingScene()
{

}

void RankingScene::Initialize()
{

}

eSceneType RankingScene::Update(const float& delta_second)
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

	// 決定
	if (input->GetButtonDown(XINPUT_BUTTON_A) || input->GetKeyDown(KEY_INPUT_E))
	{
		return eSceneType::eTitle;
	}

	Animation(delta_second);

	return GetNowSceneType();
}

void RankingScene::Draw() const
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ランキングシーン");
}

void RankingScene::Finalize()
{

}

eSceneType RankingScene::GetNowSceneType()const
{
	return eSceneType::eRanking;
}

void RankingScene::Animation(const float& delta_second)
{

}