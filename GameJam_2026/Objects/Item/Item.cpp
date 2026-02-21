#include "Item.h"
#include "DxLib.h"
#include "../GameObjectManager.h"
#include "../Character/Player/Player.h" // Playerを明示的にインクルード
#include"../../Objects/Character/PlayerClone/PlayerClone.h"

Item::Item()
{
    collision.is_blocking = true;
    collision.box_size = Vector2D(size, size);
    collision.object_type = eObjectType::eItem; // アイテムタイプ
    collision.hit_object_type.push_back(eObjectType::ePlayer); // プレイヤーに当たる


    ResourceManager* rm = ResourceManager::GetInstance();
    makimono = rm->GetImages("Resource/Images/makimono1.png")[0];
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

    DrawRotaGraphF(location.x, location.y, 0.25, 0.0, makimono, true, FALSE);

    DrawBoxAA(location.x - size / 2.0f, location.y - size / 2.0f, location.x + size / 2.0f, location.y + size / 2.0f,
        GetColor(0, 255, 0), false);
}

void Item::Finalize()
{
}

void Item::OnHitCollision(GameObject* hit_object)
{
    if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
    {
        Player* player = dynamic_cast<Player*>(hit_object);
        if (player)
        {
            collision.is_blocking = false;

            //必殺技カウント追加
            player->AddItem();

            // 色変更
            player->ChangeColorTemporarily(255, 255, 0);

            // 分身生成
            if (object_manager)
            {
                Vector2D clone_pos = player->GetLocation() + Vector2D(50, 0);
                object_manager->CreateGameObject<PlayerClone>(clone_pos);
            }
        }

        if (object_manager)
        {
            object_manager->DestroyGameObject(this);
        }
    }
}
