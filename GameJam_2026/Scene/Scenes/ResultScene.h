#pragma once
#include"../SceneBase.h"

class ResultScene : public SceneBase
{
protected:

private:
	int cursor_num = 0;

	int high_score = 0;
	int second_score = 0;
	int third_score = 0;
	int four_score = 0;
	int five_score = 0;

	int ranking[5] = {};

	int score = 0;
	int item = 0;
	int mato[3] = {};

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