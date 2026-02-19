#include "Player.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/UserTemplate.h"

Player::Player()
{
    collision.is_blocking = true;
    collision.box_size = Vector2D(120.0f, 20.0f);
    collision.object_type = eObjectType::ePlayer;
    collision.hit_object_type.push_back(eObjectType::eBall);
}

Player::~Player()
{
}

void Player::Initialize()
{
    // 画面下中央に配置
    location = Vector2D(D_WIN_MAX_X / 2.0f, D_WIN_MAX_Y - 80.0f);

    // バーサイズ
    collision.box_size = Vector2D(120.0f, 20.0f);
}

void Player::Update(float delta_seconds)
{
    Movement(delta_seconds);

    //input->Update();
     // 色タイマー減算
    if (color_timer > 0.0f)
    {
        color_timer -= delta_seconds;
        if (color_timer <= 0.0f)
        {
            // 元の色に戻す
            color_r = 255;
            color_g = 255;
            color_b = 255;
        }
    }


    //入力機能インスタンス取得
    InputManager* input = InputManager::GetInstance();

    //入力情報の更新
    input->Update();
    
    // クールタイム
    if (attack_cool > 0)
        attack_cool -= delta_seconds;
    else
        attack_cool = 0.0f;

    // アタックL
    if (input->GetKey(KEY_INPUT_L) && attack_cool <= 0.0f)
    {
        attack_cool = 1.0f;

        object_manager->CreateGameObject<Attack_L>(Vector2D(location.x, location.y - 40.0f));
    }
    
}

void Player::Draw(const Vector2D&, bool) const
{
    float halfW = collision.box_size.x * 0.5f;
    float halfH = collision.box_size.y * 0.5f;

    DrawBox(
        (int)(location.x - halfW),
        (int)(location.y - halfH),
        (int)(location.x + halfW),
        (int)(location.y + halfH),
        GetColor(color_r, color_g, color_b),
        TRUE
    );
}

void Player::Finalize()
{
}

void Player::ChangeColorTemporarily(int r, int g, int b)
{
    color_r = r;
    color_g = g;
    color_b = b;
    color_timer = 2.0f; // タイマーを2秒に固定
}

void Player::Movement(float delta_seconds)
{
    const float speed = 600.0f;
    const float deadzone = 0.2f;

    //入力機能インスタンス取得
    InputManager* input = InputManager::GetInstance();

    //入力情報の更新
    input->Update();

    float move = 0.0f;
    if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_A) ||
        input->GetButton(XINPUT_BUTTON_DPAD_LEFT) || input->GetLeftStick().x < -0.5f)
    {

        move -= 1.0;
    }

    //右移動
    if (input->GetKey(KEY_INPUT_RIGHT) || input->GetKey(KEY_INPUT_D) ||
        input->GetButton(XINPUT_BUTTON_DPAD_RIGHT) || input->GetLeftStick().x > 0.5f)
    {
        move += 1.0;
    }

   

    // 移動
    location.x += move * speed * delta_seconds;

    // 画面端制限
    float half = collision.box_size.x * 0.5f;

    if (location.x - half < 0.0f)
        location.x = half;

    if (location.x + half > D_WIN_MAX_X)
        location.x = D_WIN_MAX_X - half;
}



void Player::OnHitCollision(GameObject*)
{
}
