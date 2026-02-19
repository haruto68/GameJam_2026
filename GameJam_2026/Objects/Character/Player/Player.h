#pragma once

#include"../Character.h"
#include"PlayerStats.h"
#include "../../../Utility/InputManager.h"
#include"../../Attack/Attack_L.h"

class Player : public Character
{
protected:

private:
	int color_r = 255;
	int color_g = 255;
	int color_b = 255;

	float color_timer = 0.0f;  // 色変化タイマー
private:

	float attack_cool = 0.0f;

	PlayerStats player_stats = {};


public:

public:
	Player();
	~Player();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject*) override;

	void ChangeColorTemporarily(int r, int g, int b);
public:
	/*Vector2D GetVelocity();
	void SetVelocity(Vector2D);*/

	void Movement(float);
	/*
	void Animation(float);

	void SetPlayerStats() const;
	PlayerStats GetPlayerStats() const;*/
};