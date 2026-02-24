#include "Item_BallUp.h"
#include "DxLib.h"
#include "../GameObjectManager.h"
#include "../Character/Player/Player.h"
#include "../../Objects/Ball/Ball.h"
#include <cmath> 
#include <cstdlib> 

Item_BallUp::Item_BallUp()
{
    collision.is_blocking = true;
    collision.box_size = Vector2D(size, size);
    collision.object_type = eObjectType::eItem;
    collision.hit_object_type.push_back(eObjectType::ePlayer);

    // 画像リソースがある場合はここで読み込む
    // ResourceManager* rm = ResourceManager::GetInstance();
    // makimono = rm->GetImages("Resource/Images/ball_item.png")[0];
}

Item_BallUp::~Item_BallUp()
{
}

void Item_BallUp::Initialize()
{
}

void Item_BallUp::Update(float delta_seconds)
{
    // 下に落ちる
    location.y += 100.0f * delta_seconds;
}

void Item_BallUp::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
    // 警告回避のため int キャスト
    int x = (int)location.x;
    int y = (int)location.y;
    int r = (int)(size / 2.0f);

    // 青っぽいアイテム
    DrawCircle(x, y, r, GetColor(0, 120, 255), TRUE);

    // 四角枠もつける場合
    DrawBoxAA(x - r, y - r, x + r, y + r, GetColor(0, 255, 255), false);
}

void Item_BallUp::Finalize()
{
}

void Item_BallUp::OnHitCollision(GameObject* hit_object)
{
    if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
    {

        collision.is_blocking = false;

        Player* player = dynamic_cast<Player*>(hit_object);
        if (!player) return;

        // 色変更
        player->ChangeColorTemporarily(255, 255, 0);

        if (!object_manager) return;

        // 動いている最初のボールだけ取得（生成前にキャッシュ）
        GameObject* source_ball = nullptr;
        for (GameObject* obj : object_manager->GetObjectList())
        {
            if (obj->GetCollision().object_type == eObjectType::eBall)
            {
                source_ball = obj;
                break; // 最初のボール1つだけ
            }
        }

        // ボールが存在すれば生成
        if (source_ball)
        {
            Vector2D base_pos = source_ball->GetLocation();
            //Ball* new_ball = object_manager->CreateGameObject<Ball>(base_pos);

            Vector2D vel = source_ball->GetVelocity();
            float angle_offset = (rand() % 31 - 15) * 3.14159f / 180.0f; // ±15°
            float cosA = cos(angle_offset);
            float sinA = sin(angle_offset);
            Vector2D new_vel;
            new_vel.x = vel.x * cosA - vel.y * sinA;
            new_vel.y = vel.x * sinA + vel.y * cosA;
            //new_ball->SetVelocity(new_vel);

            player->CreateBall(base_pos, new_vel);
        }

        // アイテムは消す
        object_manager->DestroyGameObject(this);
    }
}