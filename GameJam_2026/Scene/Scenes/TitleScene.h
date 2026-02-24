#pragma once
#include"../SceneBase.h"

#define CURSOR_NUMS		(4)

class TitleScene : public SceneBase
{
protected:

private:
	int cursor_num;		//カーソル番号
	int botton = false;    //ボタン判定
	float botton_time = 0.0f;  

	int botton_image[4][2] = {};
	int background;
	int ninja_image;
	int game_rogo;

	int bgm_handle;
	int cursor_se_handle;
	int ok_handle;
public:
	TitleScene();
	~TitleScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

	void Animation(const float& delta_second);
};