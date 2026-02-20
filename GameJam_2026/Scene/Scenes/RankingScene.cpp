#include"RankingScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

RankingScene::RankingScene()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
	numbers_image[0] = rm->GetImages("Resource/Images/number0.png")[0];
	numbers_image[1] = rm->GetImages("Resource/Images/number1.png")[0];
	numbers_image[2] = rm->GetImages("Resource/Images/number2.png")[0];
	numbers_image[3] = rm->GetImages("Resource/Images/number3.png")[0];
	numbers_image[4] = rm->GetImages("Resource/Images/number4.png")[0];
	numbers_image[5] = rm->GetImages("Resource/Images/number5.png")[0];
	numbers_image[6] = rm->GetImages("Resource/Images/number6.png")[0];
	numbers_image[7] = rm->GetImages("Resource/Images/number7.png")[0];
	numbers_image[8] = rm->GetImages("Resource/Images/number8.png")[0];
	numbers_image[9] = rm->GetImages("Resource/Images/number9.png")[0];
	numbers_image[10] = 0;

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
	DrawBoxAA(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, GetColor(255, 255, 255), true);

	DrawRotaGraphF(110,110, 0.41, 0.0, numbers_image[1], true, false);
	DrawRotaGraphF(110, 240, 0.41, 0.0, numbers_image[2], true, false);  //順位
	DrawRotaGraphF(110, 370, 0.41, 0.0, numbers_image[3], true, false);
	DrawRotaGraphF(110, 500, 0.41, 0.0, numbers_image[4], true, false);
	DrawRotaGraphF(110, 630, 0.41, 0.0, numbers_image[5], true, false);

	//1位
	DrawRotaGraphF(highscore_location[0].x, highscore_location[0].y, 0.3, 0.0, numbers_image[draw_number[0]], true, false);
	DrawRotaGraphF(highscore_location[1].x, highscore_location[1].y, 0.3, 0.0, numbers_image[draw_number[1]], true, false);
	DrawRotaGraphF(highscore_location[2].x, highscore_location[2].y, 0.3, 0.0, numbers_image[draw_number[2]], true, false);
	DrawRotaGraphF(highscore_location[3].x, highscore_location[3].y, 0.3, 0.0, numbers_image[draw_number[3]], true, false);
	DrawRotaGraphF(highscore_location[4].x, highscore_location[4].y, 0.3, 0.0, numbers_image[draw_number[4]], true, false);

	//2位
	DrawRotaGraphF(secondscore_location[0].x, secondscore_location[0].y, 0.3, 0.0, numbers_image[draw_number2[0]], true, false);
	DrawRotaGraphF(secondscore_location[1].x, secondscore_location[1].y, 0.3, 0.0, numbers_image[draw_number2[1]], true, false);
	DrawRotaGraphF(secondscore_location[2].x, secondscore_location[2].y, 0.3, 0.0, numbers_image[draw_number2[2]], true, false);
	DrawRotaGraphF(secondscore_location[3].x, secondscore_location[3].y, 0.3, 0.0, numbers_image[draw_number2[3]], true, false);
	DrawRotaGraphF(secondscore_location[4].x, secondscore_location[4].y, 0.3, 0.0, numbers_image[draw_number2[4]], true, false);


	//3位
	DrawRotaGraphF(thirdscore_location[0].x, thirdscore_location[0].y, 0.3, 0.0, numbers_image[draw_number3[0]], true, false);
	DrawRotaGraphF(thirdscore_location[1].x, thirdscore_location[1].y, 0.3, 0.0, numbers_image[draw_number3[1]], true, false);
	DrawRotaGraphF(thirdscore_location[2].x, thirdscore_location[2].y, 0.3, 0.0, numbers_image[draw_number3[2]], true, false);
	DrawRotaGraphF(thirdscore_location[3].x, thirdscore_location[3].y, 0.3, 0.0, numbers_image[draw_number3[3]], true, false);
	DrawRotaGraphF(thirdscore_location[4].x, thirdscore_location[4].y, 0.3, 0.0, numbers_image[draw_number3[4]], true, false);


	//4位
	DrawRotaGraphF(fourscore_location[0].x, fourscore_location[0].y, 0.3, 0.0, numbers_image[draw_number4[0]], true, false);
	DrawRotaGraphF(fourscore_location[1].x, fourscore_location[1].y, 0.3, 0.0, numbers_image[draw_number4[1]], true, false);
	DrawRotaGraphF(fourscore_location[2].x, fourscore_location[2].y, 0.3, 0.0, numbers_image[draw_number4[2]], true, false);
	DrawRotaGraphF(fourscore_location[3].x, fourscore_location[3].y, 0.3, 0.0, numbers_image[draw_number4[3]], true, false);
	DrawRotaGraphF(fourscore_location[4].x, fourscore_location[4].y, 0.3, 0.0, numbers_image[draw_number4[4]], true, false);



	//5位
	DrawRotaGraphF(fivescore_location[0].x, fivescore_location[0].y, 0.3, 0.0, numbers_image[draw_number5[0]], true, false);
	DrawRotaGraphF(fivescore_location[1].x, fivescore_location[1].y, 0.3, 0.0, numbers_image[draw_number5[1]], true, false);
	DrawRotaGraphF(fivescore_location[2].x, fivescore_location[2].y, 0.3, 0.0, numbers_image[draw_number5[2]], true, false);
	DrawRotaGraphF(fivescore_location[3].x, fivescore_location[3].y, 0.3, 0.0, numbers_image[draw_number5[3]], true, false);
	DrawRotaGraphF(fivescore_location[4].x, fivescore_location[4].y, 0.3, 0.0, numbers_image[draw_number5[4]], true, false);
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


	//１位
	highscore_location[0] = Vector2D(D_WIN_MAX_X / 1.8, D_WIN_MAX_Y / 6);
	draw_number[0] = ((((high_score % 10000) % 1000) % 100) % 10);

	highscore_location[1] = Vector2D(D_WIN_MAX_X / 1.8 - 100, D_WIN_MAX_Y / 6);
	draw_number[1] = ((((high_score % 10000) % 1000) % 100) / 10);

	highscore_location[2] = Vector2D(D_WIN_MAX_X / 1.8 - 200, D_WIN_MAX_Y / 6);
	draw_number[2] = ((((high_score % 10000) % 1000) / 100));

	highscore_location[3] = Vector2D(D_WIN_MAX_X / 1.8 - 300, D_WIN_MAX_Y / 6);
	draw_number[3] = ((((high_score % 10000) / 1000)));

	highscore_location[4] = Vector2D(D_WIN_MAX_X / 1.8 - 400, D_WIN_MAX_Y / 6);
	draw_number[4] = ((((high_score / 10000))));


	//2位
	secondscore_location[0] = Vector2D(D_WIN_MAX_X / 1.8, D_WIN_MAX_Y / 3);
	draw_number2[0] = ((((second_score % 10000) % 1000) % 100) % 10);
	if(second_score >= 10)
	{
		secondscore_location[1] = Vector2D(D_WIN_MAX_X / 1.8 - 100, D_WIN_MAX_Y / 3);
		draw_number2[1] = ((((second_score % 10000) % 1000) % 100) / 10);
	}

	if(second_score >= 100)
	{
		secondscore_location[2] = Vector2D(D_WIN_MAX_X / 1.8 - 200, D_WIN_MAX_Y / 3);
		draw_number2[2] = ((((second_score % 10000) % 1000) / 100));
	}

	if (second_score >= 1000)
	{
		secondscore_location[3] = Vector2D(D_WIN_MAX_X / 1.8 - 300, D_WIN_MAX_Y / 3);
		draw_number2[3] = ((((second_score % 10000) / 1000)));
	}

	if(second_score >= 10000)
	{
		secondscore_location[4] = Vector2D(D_WIN_MAX_X / 1.8 - 400, D_WIN_MAX_Y / 3);
		draw_number2[4] = ((((second_score / 10000))));
	}


	//3位
	thirdscore_location[0] = Vector2D(D_WIN_MAX_X / 1.8, D_WIN_MAX_Y / 2);
	draw_number3[0] = ((((third_score % 10000) % 1000) % 100) % 10);
	if (third_score >= 10)
	{
		thirdscore_location[1] = Vector2D(D_WIN_MAX_X / 1.8 - 100, D_WIN_MAX_Y / 2);
		draw_number3[1] = ((((third_score % 10000) % 1000) % 100) / 10);
	}

	if (third_score >= 100)
	{
		thirdscore_location[2] = Vector2D(D_WIN_MAX_X / 1.8 - 200, D_WIN_MAX_Y / 2);
		draw_number3[2] = ((((third_score % 10000) % 1000) / 100));
	}

	if (third_score >= 1000)
	{
		thirdscore_location[3] = Vector2D(D_WIN_MAX_X / 1.8 - 300, D_WIN_MAX_Y / 2);
		draw_number3[3] = ((((third_score % 10000) / 1000)));
	}

	if (third_score >= 10000)
	{
		thirdscore_location[4] = Vector2D(D_WIN_MAX_X / 1.8 - 400, D_WIN_MAX_Y / 2);
		draw_number3[4] = ((((third_score / 10000))));
	}



	//4位
	fourscore_location[0] = Vector2D(D_WIN_MAX_X / 1.8, D_WIN_MAX_Y / 1.5);
	draw_number4[0] = ((((four_score % 10000) % 1000) % 100) % 10);
	if (four_score >= 10)
	{
		fourscore_location[1] = Vector2D(D_WIN_MAX_X / 1.8 - 100, D_WIN_MAX_Y / 1.5);
		draw_number4[1] = ((((four_score % 10000) % 1000) % 100) / 10);
	}

	if (four_score >= 100)
	{
		fourscore_location[2] = Vector2D(D_WIN_MAX_X / 1.8 - 200, D_WIN_MAX_Y / 1.5);
		draw_number4[2] = ((((four_score % 10000) % 1000) / 100));
	}

	if (four_score >= 1000)
	{
		fourscore_location[3] = Vector2D(D_WIN_MAX_X / 1.8 - 300, D_WIN_MAX_Y / 1.5);
		draw_number4[3] = ((((four_score % 10000) / 1000)));
	}

	if (four_score >= 10000)
	{
		fourscore_location[4] = Vector2D(D_WIN_MAX_X / 1.8 - 400, D_WIN_MAX_Y / 1.5);
		draw_number4[4] = ((((four_score / 10000))));
	}



	//5位
	fivescore_location[0] = Vector2D(D_WIN_MAX_X / 1.8, D_WIN_MAX_Y / 1.17);
	draw_number5[0] = ((((five_score % 10000) % 1000) % 100) % 10);
	if (five_score >= 10)
	{
		fivescore_location[1] = Vector2D(D_WIN_MAX_X / 1.8 - 100, D_WIN_MAX_Y / 1.17);
		draw_number5[1] = ((((five_score % 10000) % 1000) % 100) / 10);
	}

	if (five_score >= 100)
	{
		fivescore_location[2] = Vector2D(D_WIN_MAX_X / 1.8 - 200, D_WIN_MAX_Y / 1.17);
		draw_number5[2] = ((((five_score % 10000) % 1000) / 100));
	}

	if (five_score >= 1000)
	{
		fivescore_location[3] = Vector2D(D_WIN_MAX_X / 1.8 - 300, D_WIN_MAX_Y / 1.17);
		draw_number5[3] = ((((five_score % 10000) / 1000)));
	}

	if (five_score >= 10000)
	{
		fivescore_location[4] = Vector2D(D_WIN_MAX_X / 1.8 - 400, D_WIN_MAX_Y / 1.17);
		draw_number5[4] = ((((five_score / 10000))));
	}



}