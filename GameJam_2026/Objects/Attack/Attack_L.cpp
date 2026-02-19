#include "Attack_L.h"

Attack_L::Attack_L()
{
	collision.is_blocking = true;
	collision.box_size = Vector2D(120.0f, 50.0f);
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eBall);

}

Attack_L::~Attack_L()
{

}

void Attack_L::Initialize()
{
	
}

void Attack_L::Update(float delta_seconds)
{
	cool_time += delta_seconds;

	if (cool_time >= 0.5f)
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


	switch (type)
	{
	case ePlayer:
		break;
	case eBlock:
		break;
	default:
		break;
	}
}

void Attack_L::Movement(float delta_seconds)
{

}

void Attack_L::Animation(float delta_seconds)
{

}

