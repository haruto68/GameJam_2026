#pragma once

#include"../Character.h"
#include"PlayerStats.h"
#include "../../../Utility/InputManager.h"
#include"../../Attack/Attack_L.h"
#include"../../Attack/Attack_R.h"
//#include"../PlayerClone/PlayerClone.h"

class Player : public Character
{

private:
	float life;       // 現在のライフ
	float max_life;   // 最大ライフ

	float attack_cool = 0.0f;
	float stan_time = 0.0f;

	int ninja_idle[4] = {};
	int ninja_run[8] = {};
	int anime_num = 0;
	float anime_cool = 0.0f;

	int stan_image = 0;
	int stan_images[4] = {};
	int stan_anime_num = 0;
	float stan_anime_cool = 0.0f;

private:
	int color_r = 255;
	int color_g = 255;
	int color_b = 255;

	float color_timer = 0.0f;  // 色変化タイマー

	int item_count = 0;

	bool is_special_active = false;
	float special_timer = 0.0f;

public:
	Player();
	~Player();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject*) override;

public:
	/*Vector2D GetVelocity();
	void SetVelocity(Vector2D);*/

	void Movement(float);
	void Animation(float);

public:
	void TakeDamage(float amount);            // ダメージを受ける
	float GetLife() const { return life; }
	float GetMaxLife() const { return max_life; }
	void AddItem();
	void ChangeColorTemporarily(int r, int g, int b);
	void DrawKari()const;
	void DrawUI()const;

public:
	void Attack(float);
	void CreateBall();
	void CreateBall(Vector2D, Vector2D);
};