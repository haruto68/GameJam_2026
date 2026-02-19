#include "Block.h"
#include "DxLib.h"
#include"../../Objects/GameObjectManager.h"
#include"../../Objects/Item/Item.h"

void Block::OnHitCollision(GameObject* hit_object)
{
    // 衝突対象が Ball の場合
    if (hit_object->GetCollision().object_type == eObjectType::eBall)
    {
        // まだアイテム生成していなければ
        if (!item_spawned)
        {
            item_spawned = true; // フラグを先に立てる → 安全

            // 1/3 の確率でアイテム生成
            if (rand() % 3 == 0)
            {
                if (object_manager)
                {
                    object_manager->CreateGameObject<Item>(location);
                }
            }
        }

        // 自分の削除は必ず行う
        if (object_manager)
        {
            object_manager->DestroyGameObject(this);
        }
    }
}



Block::Block(/*const Vector2D& pos*/)
{
    //location = pos;
    size = Vector2D(100.0f, 30.0f);

    collision.box_size = size;
    collision.is_blocking = true;
    collision.object_type = eObjectType::eBlock;
    collision.hit_object_type.push_back(eObjectType::eBall);

    z_layer = 1;
    is_mobility = false;
}

Block::~Block()
{
}

void Block::Initialize()
{
}

void Block::Update(float)
{
}

void Block::Draw(const Vector2D&, bool) const
{
    float halfW = size.x * 0.5f;
    float halfH = size.y * 0.5f;

    DrawBox(
        (int)(location.x - halfW),
        (int)(location.y - halfH),
        (int)(location.x + halfW),
        (int)(location.y + halfH),
        GetColor(0, 200, 255),
        TRUE
    );
}

void Block::Finalize()
{
}
