#include "Attack_R.h"

Attack_R::Attack_R()
{
	collision.is_blocking = true;
	collision.box_size = Vector2D(120.0f, 50.0f);
	collision.object_type = eObjectType::eAttack;
	collision.hit_object_type.push_back(eObjectType::eBall);

}

Attack_R::~Attack_R()
{

}

void Attack_R::Initialize()
{

}

void Attack_R::Update(float delta_seconds)
{
	cool_time += delta_seconds;

	if (cool_time >= 0.5f)
	{
		object_manager->DestroyGameObject(this);
	}

	Movement(delta_seconds);
	Animation(delta_seconds);
}

void Attack_R::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	float size_x = collision.box_size.x / 2;
	float size_y = collision.box_size.y / 2;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
	DrawBoxAA(location.x - size_x, location.y - size_y, location.x + size_x, location.y + size_y,
		GetColor(255, 255, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Attack_R::Finalize()
{

}

void Attack_R::OnHitCollision(GameObject* hit_object)
{
	eObjectType type = hit_object->GetCollision().object_type;

	// ƒ{[ƒ‹‚ð‰Eã‚É”ò‚Î‚·
	if (type == eBall)
	{
		float vel_x = 2.0f - (cool_time * 5.0f);
		hit_object->SetVelocity(Vector2D(vel_x, -1.0f));
	}
}

void Attack_R::Movement(float delta_seconds)
{

}

void Attack_R::Animation(float delta_seconds)
{

}

