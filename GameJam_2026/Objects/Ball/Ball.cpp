#include "Ball.h"

Ball::Ball()
{
	collision.is_blocking = true;
	collision.box_size = Vector2D(radius, radius);
	collision.object_type = eObjectType::eBall;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);

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
	DrawCircle(location.x,location.y, radius, GetColor(255, 255, 255), TRUE);
	DrawBoxAA(location.x - radius, location.y - radius, location.x + radius, location.y + radius,
		GetColor(255, 0, 0), false);
}

void Ball::Finalize()
{

}

void Ball::OnHitCollision(GameObject* hit_object)
{
	eObjectType type = hit_object->GetCollision().object_type;


	Vector2D hit_loc = hit_object->GetLocation();
	

	switch (type)
	{
	case ePlayer:
		// 反射
		if (hit_loc.y > location.y)
			velocity.y = -1.0f;
		else
			velocity.y = 1.0f;
		break;
	case eBlock:
		// 反射
		if (hit_loc.y > location.y)
			velocity.y = -1.0f;
		else
			velocity.y = 1.0f;
		break;
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

