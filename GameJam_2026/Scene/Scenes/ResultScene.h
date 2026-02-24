#pragma once
#include"../SceneBase.h"

#define  DIGIT   5

class ResultScene : public SceneBase
{
protected:

private:
	int background_makimono = 0;
	int cursor_num = 0;
	int numbers_image[11] = {};
	int draw_number[DIGIT] = { 10,10,10,10,10 };
	int draw_number2[DIGIT] = { 10,10,10,10,10 };
	int draw_number3[DIGIT] = { 10,10,10,10,10 };
	int draw_number4[DIGIT] = { 10,10,10,10,10 };
	int draw_number5[DIGIT] = { 10,10,10,10,10 };
	int draw_number6[DIGIT] = { 10,10,10,10,10 };
	int draw_number7[DIGIT] = { 10,10,10,10,10 };
	int draw_number8[DIGIT] = { 10,10,10,10,10 };

	int botton = false;
	int botton_image[3][3] = {};
	float botton_time = 0;
	int mato1_image;
	int mato2_image;
	int item_image;
	int item_score = 0;
	int mato1_score = 0;
	int mato2_score = 0;
	int kakeru_image;
	int ikoru_image;
	int highscore_image;
	int score_image;

	int high_score = 0;
	int second_score = 0;
	int third_score = 0;
	int four_score = 0;
	int five_score = 0;

	int ranking[5] = {};

	int score = 0;
	int item = 0;
	int mato[3] = {};

	int Result_handle;


public:
	ResultScene();
	~ResultScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

	void Animation(const float& delta_second);
};