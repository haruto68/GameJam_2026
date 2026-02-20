#include "Ball.h"

bool Ball::is_penetrating = false;

Ball::Ball()
{
	collision.is_blocking = true;
	collision.box_size = Vector2D(radius, radius);
	collision.object_type = eObjectType::eBall;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::eClone);
	collision.hit_object_type.push_back(eObjectType::eAttack);

	ResourceManager* rm = ResourceManager::GetInstance();
	syuriken_image[0] = rm->GetImages("Resource/Images/syuriken1.png")[0];
	syuriken_image[1] = rm->GetImages("Resource/Images/syuriken2.png")[0];
	syuriken_image[2] = rm->GetImages("Resource/Images/syuriken3.png")[0];
	syuriken_image[3] = rm->GetImages("Resource/Images/syuriken4.png")[0];

	image = syuriken_image[0];

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
	//DrawCircle(location.x,location.y, radius, GetColor(255, 255, 255), TRUE);
	DrawRotaGraphF(location.x, location.y, 0.3, angle, image, true, FALSE);
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
	case eClone:
		// プレイヤー・クローンは必ず反射
		if (velocity.y < 0)
			velocity.y = velocity.y * -1.0;
		if (hit_loc.y > location.y)
			velocity.y *= -1.0f;
		else
			velocity.y *= 1.0f;
		break;

	case eBlock:
		// 必殺技中なら反射しない
		if (!is_penetrating)
		{
			if (velocity.y < 0)
				velocity.y = velocity.y * -1.0;
			if (hit_loc.y > location.y)
				velocity.y *= -1.0f;
			else
				velocity.y *= 1.0f;
		}
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
	animation_time += delta_seconds;
	syuriken_time += delta_seconds;

	if (animation_time >= 0.1f)
	{
		animation_time = 0.0f;
		anim_num++;
		if (anim_num > 3)
		{
			anim_num = 0;
		}
		image = syuriken_image[anim_num];

	}

	if (syuriken_time >= 0.01f)
	{
		syuriken_time = 0.0f;
		angle += angle_pluse;
		if (angle > π * 2 || angle < -π * 2)
			angle = 0;
	}
}