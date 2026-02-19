#pragma once
#include "../GameObject.h"
#include"../GameObjectManager.h"

class Attack_R : public GameObject
{
private:
	float cool_time = 0.0f;

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