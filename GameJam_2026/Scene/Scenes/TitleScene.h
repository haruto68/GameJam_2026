#pragma once
#include"../SceneBase.h"

#define CURSOR_NUMS		(5)

class TitleScene : public SceneBase
{
protected:

private:
	int cursor_num;		//ÉJÅ[É\Éãî‘çÜ

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