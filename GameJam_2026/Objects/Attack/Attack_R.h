#pragma once
#include "../GameObject.h"
#include"../GameObjectManager.h"

class Attack_R : public GameObject
{
private:
	Vector2D size;
	float cool_time = 0.0f;
	float life_time = 0.6f;

	int attack_image[4] = {};
	int anime_num = 0;
	float anime_cool = 0.0f;

	Vector2D target_R[10] = {};	//ハジク方向

	Vector2D footprints = 0;	//プレイヤーの移動量確認用
	int kakinki_handle;
public:
	Attack_R();
	~Attack_R();


public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject*) override;

public:
	void Movement(float);
	void Animation(float);

};