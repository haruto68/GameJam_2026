#pragma once
#include"../SceneBase.h"

class HelpScene : public SceneBase
{
protected:

private:
	int background_makimono = 0;
	int background;
	int controller;
	int a_botton;
	int lb_image;
	int rb_image;
	int juuji;

	int botton_image[2];
	int botton = false;
	float botton_time = 0.0;

public:
	HelpScene();
	~HelpScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

	void Animation(const float& delta_second);
};