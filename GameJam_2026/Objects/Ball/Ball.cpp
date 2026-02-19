#include "Ball.h"

Ball::Ball()
{

}

Ball::~Ball()
{

}

void Ball::Initialize()
{
	velocity.x = 1.0f;
	velocity.y = 1.0f;
}

void Ball::Update(float delta_seconds)
{
    Movement(delta_seconds);
    Animation(delta_seconds);


    
}

void Ball::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	DrawCircle(location.x,location.y, 10.0, GetColor(255, 255, 255), TRUE);
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

	// --- 2. 壁での反射処理 ---
   //上画面端
	if ((location.y + velocity.y) < (0) - (collision.box_size.y / 2.0f))
	{
		if ((location.y + velocity.y) < location.y)
		{
			velocity.y *= -1.0f;
		}
	}
	//下画面端
	if ((location.y + velocity.y) >= (720) - (collision.box_size.y / 2.0f))
	{
		if ((location.y + velocity.y) > location.y)
		{
			velocity.y *= -1.0f;
		}
	}
	//左画面端
	if ((location.x + velocity.x) < (collision.box_size.x / 2.0f))
	{
		if ((location.x + velocity.x) < location.x)
		{
			velocity.x *= -1.0f;
		}
	}
	//右画面端
	if ((location.x + velocity.x) >= (D_WIN_MAX_X)-(collision.box_size.x / 2.0f))
	{
		if ((location.x + velocity.x) > location.x)
		{
			velocity.x *= -1.0f;
		}
	}




	float speed = 500.0f;


	//座標決定
	location += velocity * speed *  delta_seconds;
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
