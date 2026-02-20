#include "PlayerClone.h"
#include "../../../Utility/Vector2D.h"
#include "../../../Objects/GameObjectManager.h"
#include "DxLib.h"
#include <cmath>
#include <cstdlib> 
#include <ctime>   
PlayerClone::PlayerClone()
{
    collision.is_blocking = true;
    collision.box_size = Vector2D(120.0f, 20.0f);
    collision.object_type = eObjectType::eClone;
    collision.hit_object_type.push_back(eObjectType::eBall);

    // ランダムで右(1)か左(-1)に移動
    move_direction = (rand() % 2 == 0) ? 1 : -1;
    speed = 400.0f;      // 移動速度
    life_time = 5.0f;    // 生存時間
}

PlayerClone::~PlayerClone()
{
}

void PlayerClone::Initialize()
{
    // 必要なら初期位置を設定
}

void PlayerClone::Update(float delta_seconds)
{
    // 左右に自動移動
    location.x += move_direction * speed * delta_seconds;

    //// 画面端で方向反転
    //float halfW = collision.box_size.x * 0.5f;
    //if (location.x - halfW < 0.0f)
    //{
    //    location.x = halfW;
    //    move_direction = 1;
    //}
    float halfW = collision.box_size.x * 0.5f;

    int gauge_width = 200;
    int margin = 30;

    // ゲージ左端
    float gauge_left = D_WIN_MAX_X - margin - gauge_width;

    // 左端
    if (location.x - halfW < 0.0f)
    {
        location.x = halfW;
        move_direction = 1;
    }
    // 右端（ゲージまで）
    else if (location.x + halfW > gauge_left)
    {
        location.x = gauge_left - halfW;
        move_direction = -1;
    }

    // 生存時間が過ぎたら消える
    life_time -= delta_seconds;
    if (life_time <= 0.0f && object_manager)
    {
        object_manager->DestroyGameObject(this);
    }
}

void PlayerClone::Draw(const Vector2D&, bool) const
{
    float halfW = collision.box_size.x * 0.5f;
    float halfH = collision.box_size.y * 0.5f;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
    DrawBox(
        (int)(location.x - halfW),
        (int)(location.y - halfH),
        (int)(location.x + halfW),
        (int)(location.y + halfH),
        GetColor(255, 255, 255),
        TRUE
    );
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
