#pragma once
#include "../GameObject.h"
#include"../GameObjectManager.h"

class Ball : public GameObject
{
private:
	Vector2D velocity = 0.0f;
	int hit_point = 0;
	int anime_count = 0;
	bool flip_flag = false;

public:
	Ball();
	~Ball();


public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject*) override;

public:
	void Movement(float);
	void Animation(float);

	Vector2D GetVelocity();
	void SetVelocity(Vector2D);

};