#include "Ball.h"

Ball::Ball()
{

}

Ball::~Ball()
{

}

void Ball::Initialize()
{

}

void Ball::Update(float delta_seconds)
{

}

void Ball::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	DrawCircle(location.x,location.y, 3.0, GetColor(255, 255, 255), TRUE);
}

void Ball::Finalize()
{

}

void Ball::OnHitCollision(GameObject* hit_object)
{
	eObjectType type = hit_object->GetCollision().object_type;

	switch (type)
	{
	default:
		break;
	}
}

void Ball::Movement(float delta_seconds)
{

}

void Ball::Animation(float delta_seconds)
{

}

Vector2D Ball::GetVelocity()
{
	return this->velocity;
}

void Ball::SetVelocity(Vector2D velocity)
{
	this->velocity += velocity;
}
