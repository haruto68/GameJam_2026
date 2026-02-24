#include "Player.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/UserTemplate.h"
#include "../../../Objects/Item/Item.h"
#include "../../../Objects/Ball/Ball.h"
#include"../PlayerClone/PlayerClone.h"
#include "../../../Objects/GameObject.h"
#include"../../../Objects/GameObjectManager.h"
#include "DxLib.h"

// ゲージ関連定数
constexpr int GAUGE_WIDTH = 200;
constexpr int GAUGE_HEIGHT = 20;
constexpr int GAUGE_MARGIN = 30;

Player::Player() : max_life(5.0f), life(5.0f)
{
    collision.is_blocking = true;
    collision.box_size = Vector2D(120.0f, 100.0f);
    collision.object_type = eObjectType::ePlayer;
    collision.hit_object_type.push_back(eObjectType::eBall);

    ResourceManager* rm = ResourceManager::GetInstance();
    ninja_idle[0] = rm->GetImages("Resource/Images/ninja_idle1.png")[0];
    ninja_idle[1] = rm->GetImages("Resource/Images/ninja_idle2.png")[0];
    ninja_idle[2] = rm->GetImages("Resource/Images/ninja_idle3.png")[0];
    ninja_idle[3] = rm->GetImages("Resource/Images/ninja_idle4.png")[0];
    ninja_run[0] = rm->GetImages("Resource/Images/ninja_run1.png")[0];
    ninja_run[1] = rm->GetImages("Resource/Images/ninja_run2.png")[0];
    ninja_run[2] = rm->GetImages("Resource/Images/ninja_run3.png")[0];
    ninja_run[3] = rm->GetImages("Resource/Images/ninja_run4.png")[0];
    ninja_run[4] = rm->GetImages("Resource/Images/ninja_run5.png")[0];
    ninja_run[5] = rm->GetImages("Resource/Images/ninja_run6.png")[0];
    ninja_run[6] = rm->GetImages("Resource/Images/ninja_run7.png")[0];
    ninja_run[7] = rm->GetImages("Resource/Images/ninja_run8.png")[0];

    image = ninja_idle[0];
}

Player::~Player()
{
}

void Player::Initialize()
{
    // 画面下中央に配置
    location = Vector2D(525.0f, 660.0f);
}

void Player::Update(float delta_seconds)
{

    // 色タイマー更新
    if (color_timer > 0.0f)
        color_timer -= delta_seconds;

    // 貫通弾管理
    if (is_special_active)
    {
        special_timer -= delta_seconds;

        if (special_timer <= 0.0f)
            is_special_active = false;
    }

    // アタッククールタイム管理
    if (attack_cool > 0)
        attack_cool -= delta_seconds;
    else
        attack_cool = 0.0f;

    // スタンクールタイム
    if (stan_time > 0.0f)
        stan_time -= delta_seconds;
    else
    {
        stan_time = 0.0f;
        Movement(delta_seconds);
        Attack(delta_seconds);
    }
    Animation(delta_seconds);

}

void Player::Draw(const Vector2D&, bool) const
{
    
    //DrawKari();

    DrawRotaGraphF(location.x, location.y, 0.5, 0.0, image, TRUE, flip_flag);

    // 仮ボックス
    int color = GetColor(255, 0, 255);
    if (stan_time > 0)color = GetColor(0, 0, 255);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
    DrawBoxAA(
        location.x - collision.box_size.x / 2, location.y - collision.box_size.y / 2,
        location.x + collision.box_size.x / 2, location.y + collision.box_size.y / 2,
        color, false);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

    DrawUI();
}

void Player::Movement(float delta_seconds)
{
    const float speed = 600.0f;
    /*const float deadzone = 0.2f;*/

    //入力機能インスタンス取得
    InputManager* input = InputManager::GetInstance();


    velocity.x = 0.0f;

    if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_A) ||
        input->GetButton(XINPUT_BUTTON_DPAD_LEFT) || input->GetLeftStick().x < -0.5f)
    {
        velocity.x = -1.0f;
        flip_flag = false;
    }

    //右移動
    if (input->GetKey(KEY_INPUT_RIGHT) || input->GetKey(KEY_INPUT_D) ||
        input->GetButton(XINPUT_BUTTON_DPAD_RIGHT) || input->GetLeftStick().x > 0.5f)
    {
        velocity.x = 1.0f;
        flip_flag = true;
    }

    // アイテム使用
    if (!is_special_active && item_count >= 2 && input->GetButton(XINPUT_BUTTON_A))
    {
        is_special_active = true;
        special_timer = 3.0f;
        item_count = 0;
    }




    // 移動
    location += velocity * speed * delta_seconds;

    // 画面端制限（右端はゲージ左端まで）
    float half = collision.box_size.x * 0.5f;
    float gauge_left = D_WIN_MAX_X - GAUGE_MARGIN - GAUGE_WIDTH;

    if (location.x - half < 0.0f) location.x = half;
    if (location.x + half > gauge_left) location.x = gauge_left - half;

}

void Player::Animation(float delta_seconds)
{
    anime_cool += delta_seconds;

    if (velocity.x == 0.0f)
    {
        if (anime_cool > 0.1f)
        {
            anime_cool = 0.0f;
            anime_num++;

            if (anime_num > 3)
                anime_num = 0;

            image = ninja_idle[anime_num];
        }
    }
    else
    {
        if (anime_cool > 0.05f)
        {
            anime_cool = 0.0f;
            anime_num++;

            if (anime_num > 7)
                anime_num = 0;

            image = ninja_run[anime_num];
        }
    }


}

void Player::Finalize()
{
}

void Player::OnHitCollision(GameObject* other)
{
    if (!other) return;

    // 他のオブジェクトがボールなら
    if (other->GetCollision().object_type == eObjectType::eBall)
    {
        stan_time = 1.0f;
        velocity = 0.0f;

        // ダメージ量
        TakeDamage(0.5f);

        // 当たったら一瞬色を変える（赤く光らせる）
        ChangeColorTemporarily(255, 0, 0);
    }

    // アイテムに触れた場合
    if (dynamic_cast<Item*>(other) != nullptr)
    {
        //クローン生成
        object_manager->CreateGameObject<PlayerClone>(location);
    }

}

void Player::TakeDamage(float amount)
{
    life -= amount;
    if (life < 0.0f)
        life = 0.0f;  // 0以下になったら死亡扱い
}

// アイテムを取得
void Player::AddItem()
{
    item_count++;
}

void Player::ChangeColorTemporarily(int r, int g, int b)
{
    color_r = r;
    color_g = g;
    color_b = b;
    color_timer = 2.0f;
}

void Player::DrawKari()const
{
    float halfW = collision.box_size.x * 0.5f;
    float halfH = collision.box_size.y * 0.5f;

    int r = 255, g = 255, b = 255;

    if (is_special_active)
    {
        r = 255; g = 0; b = 0;
    }

    if (stan_time > 0.0f)
        r = 0, g = 0, b = 255;
    else
        r = 255, g = 255, b = 255;


    // プレイヤー本体描画
    DrawBox(
        (int)(location.x - halfW),
        (int)(location.y - halfH),
        (int)(location.x + halfW),
        (int)(location.y + halfH),
        GetColor(r, g, b),
        TRUE
    );
}

void Player::DrawUI()const
{
    // --- 必殺技ゲージ（既存） ---
    int gauge_x1 = D_WIN_MAX_X - GAUGE_MARGIN - GAUGE_WIDTH;
    int gauge_y1 = GAUGE_MARGIN;
    int gauge_x2 = D_WIN_MAX_X - GAUGE_MARGIN;
    int gauge_y2 = GAUGE_MARGIN + GAUGE_HEIGHT;

    DrawBox(gauge_x1 + 15, gauge_y1, gauge_x2 + 15, gauge_y2, GetColor(50, 50, 50), TRUE);
    float rate = is_special_active ? special_timer / 3.0f : item_count / 2.0f;
    if (rate > 1.0f) rate = 1.0f;
    if (rate < 0.0f) rate = 0.0f;
    DrawBox(gauge_x1 + 15, gauge_y1, gauge_x1 + 15 + (int)(GAUGE_WIDTH * rate), gauge_y2, GetColor(255, 0, 0), TRUE);
    DrawBox(gauge_x1 + 15, gauge_y1, gauge_x2 + 15, gauge_y2, GetColor(255, 255, 255), FALSE);



    // プレイヤー移動制限線（右端）
    float half = collision.box_size.x * 0.5f;
    float gauge_left = D_WIN_MAX_X - GAUGE_MARGIN - GAUGE_WIDTH;
    DrawLine((int)gauge_left, 0, (int)gauge_left, D_WIN_MAX_Y, GetColor(255, 255, 255));

    // 左端も線にしたい場合
    //DrawLine(0, 0, 0, D_WIN_MAX_Y, GetColor(255, 255, 255));

    //// --- ライフゲージ（右上、必殺技ゲージの下） ---
    //int life_x1 = D_WIN_MAX_X - GAUGE_MARGIN - GAUGE_WIDTH;
    //int life_y1 = GAUGE_MARGIN + GAUGE_HEIGHT + 10; // 必殺技ゲージの下に10px空ける
    //int life_x2 = D_WIN_MAX_X - GAUGE_MARGIN;
    //int life_y2 = life_y1 + GAUGE_HEIGHT;

    //// 背景
    //DrawBox(life_x1 + 15, life_y1, life_x2 + 15, life_y2, GetColor(50, 50, 50), TRUE);
    //// ライフ割合
    //float life_rate = life / max_life;
    //if (life_rate < 0.0f) life_rate = 0.0f;
    //DrawBox(life_x1 + 15, life_y1, life_x1 + 15 + (int)(GAUGE_WIDTH * life_rate), life_y2, GetColor(0, 255, 0), TRUE);

    //// 枠
    //DrawBox(life_x1 + 15, life_y1, life_x2 + 15, life_y2, GetColor(255, 255, 255), FALSE);

}

// 攻撃処理
void Player::Attack(float delta_seconds)
{

    //入力機能インスタンス取得
    InputManager* input = InputManager::GetInstance();

    // アタックL
    if ((input->GetKey(KEY_INPUT_J) || input->GetButton(XINPUT_BUTTON_LEFT_SHOULDER))
        && attack_cool <= 0.0f)
    {
        attack_cool = 0.8f;
        object_manager->CreateGameObject<Attack_L>(Vector2D(location.x, location.y - 80.0f));
    }
    // アタックR
    if ((input->GetKey(KEY_INPUT_K) || input->GetButton(XINPUT_BUTTON_RIGHT_SHOULDER))
        && attack_cool <= 0.0f)
    {
        attack_cool = 0.8f;
        object_manager->CreateGameObject<Attack_R>(Vector2D(location.x, location.y - 80.0f));
    }
}

// ボール生成
void Player::CreateBall()
{
    if(object_manager)
    {
        Ball* ball = object_manager->CreateGameObject<Ball>(Vector2D(location.x, location.y - 75.0f));
        ball->SetVelocity(Vector2D(0, 0));
    }
}

// 追加ボール生成
void Player::CreateBall(Vector2D set_location, Vector2D set_velocity)
{
    if (object_manager)
    {
        Ball* ball = object_manager->CreateGameObject<Ball>(set_location);
        ball->SetVelocity(set_velocity);
    }
}