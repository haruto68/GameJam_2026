#include "Item.h"
#include "DxLib.h"
#include "../GameObjectManager.h"
Item::Item()
{
    collision.is_blocking = true;
    collision.box_size = Vector2D(size, size);
    collision.object_type = eObjectType::eItem; // 新しいタイプ
    collision.hit_object_type.push_back(eObjectType::ePlayer); // プレイヤーに当たる
}

Item::~Item()
{
}

void Item::Initialize()
{
}

void Item::Update(float delta_seconds)
{
    // ここで簡単なアニメーションや落下などを実装できる
    location.y += 1;
}

void Item::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
    DrawCircle(location.x, location.y, size / 2.0f, GetColor(255, 255, 0), TRUE);
}

void Item::Finalize()
{
}

void Item::OnHitCollision(GameObject* hit_object)
{
    if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
    {
        // プレイヤーに拾われたときの処理
        // スコア加算など
        object_manager->DestroyGameObject(this);
    }
}
