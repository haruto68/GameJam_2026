#pragma once
#include"../SceneBase.h"

#define  DIGIT   5

class RankingScene : public SceneBase
{
protected:

private:
	int numbers_image[11] = {};
	int botton_image[2];
	int botton = false;
	float botton_time = 0.0;

	int high_score = 12345;
	int second_score = 2345;
	int third_score = 345;
	int four_score = 45;
	int five_score = 5;

	Vector2D highscore_location[DIGIT] = {};
	Vector2D secondscore_location[DIGIT] = {};
	Vector2D thirdscore_location[DIGIT] = {};
	Vector2D fourscore_location[DIGIT] = {};
	Vector2D fivescore_location[DIGIT] = {};
	int draw_number[DIGIT] = { 10,10,10,10,10 };
	int draw_number2[DIGIT] = { 10,10,10,10,10 };
	int draw_number3[DIGIT] = { 10,10,10,10,10 };
	int draw_number4[DIGIT] = { 10,10,10,10,10 };
	int draw_number5[DIGIT] = { 10,10,10,10,10 };


public:
	RankingScene();
	~RankingScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

	void Animation(const float& delta_second);
};