#include "Attack_L.h"

Attack_L::Attack_L()
{
	collision.is_blocking = true;
	collision.box_size = Vector2D(120.0f, 50.0f);
	collision.object_type = eObjectType::eAttack;
	collision.hit_object_type.push_back(eObjectType::eBall);

}

Attack_L::~Attack_L()
{

}

void Attack_L::Initialize()
{
	target_L[0] = Vector2D(-5.0f, -1.0f);	//81°
	target_L[1] = Vector2D(-5.0f, -2.0f);	//72°
	target_L[2] = Vector2D(-5.0f, -3.0f);	//63°
	target_L[3] = Vector2D(-5.0f, -4.0f);	//54°
	target_L[4] = Vector2D(-5.0f, -5.0f);	//45°
	target_L[5] = Vector2D(-4.0f, -5.0f);	//36°
	target_L[6] = Vector2D(-3.0f, -5.0f);	//27°
	target_L[7] = Vector2D(-2.0f, -5.0f);	//18°
	target_L[8] = Vector2D(-1.0f, -5.0f);	//9°
	target_L[9] = Vector2D(0.0f, -5.0f);	//0°
}

void Attack_L::Update(float delta_seconds)
{
	cool_time += delta_seconds;

	if (cool_time >= life_time)
	{
		object_manager->DestroyGameObject(this);
	}

	Movement(delta_seconds);
	Animation(delta_seconds);
}

void Attack_L::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	float size_x = collision.box_size.x / 2;
	float size_y = collision.box_size.y / 2;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
	DrawBoxAA(location.x - size_x, location.y - size_y, location.x + size_x, location.y + size_y,
		GetColor(0, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Attack_L::Finalize()
{

}

void Attack_L::OnHitCollision(GameObject* hit_object)
{
	eObjectType type = hit_object->GetCollision().object_type;

	// ボールを左上に飛ばす
	if (type == eBall)
	{
		// 早い程左に、遅いほど上にハジク
		for (int i = 9; i >= 0; i--)
		{
			if (cool_time <= (life_time / 10) * i)
			{
				//加速度設定
				Vector2D target = Vector2D(location.x + target_L[i].x, location.y + target_L[i].y);
				Vector2D target_velocity = Tracking(location, target);

				hit_object->SetVelocity(target_velocity);
			}
		}
	}
}

void Attack_L::Movement(float delta_seconds)
{

}

void Attack_L::Animation(float delta_seconds)
{

}

