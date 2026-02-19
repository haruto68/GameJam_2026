#pragma once

#include"../Character.h"
#include"PlayerStats.h"

class Player : public Character
{
protected:

private:

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

public:
	Vector2D GetVelocity();
	void SetVelocity(Vector2D);

	void Movement(float);
	void Animation(float);

	void SetPlayerStats() const;
	PlayerStats GetPlayerStats() const;
};