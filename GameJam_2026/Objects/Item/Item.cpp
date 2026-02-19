#include "Item.h"
#include "DxLib.h"
#include "../GameObjectManager.h"
#include "../Character/Player/Player.h" // Playerを明示的にインクルード

Item::Item()
{
    collision.is_blocking = true;
    collision.box_size = Vector2D(size, size);
    collision.object_type = eObjectType::eItem; // アイテムタイプ
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
    // 下に落ちる
    location.y += 100.0f * delta_seconds; // 落下スピード調整
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
        // Player にキャストして色を変える
        Player* player = dynamic_cast<Player*>(hit_object);
        if (player)
        {
            player->ChangeColorTemporarily(255, 255, 0); // 黄色に2秒だけ
        }

        // 自分を削除
        if (object_manager)
        {
            object_manager->DestroyGameObject(this);
        }
    }
}
