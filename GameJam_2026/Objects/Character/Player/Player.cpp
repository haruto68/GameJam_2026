#include "Player.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/UserTemplate.h"

Player::Player()
{
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
        GetColor(255, 255, 255),
        TRUE
    );
}

void Player::Finalize()
{
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
    if (input->GetKey(KEY_INPUT_LEFT) ||input->GetKey(KEY_INPUT_A)||
        input->GetButton(XINPUT_BUTTON_DPAD_LEFT) || input->GetLeftStick().x < -0.5f)
    {

        move -= 1.0;
    }
    
    //右移動
if ( input->GetKey(KEY_INPUT_RIGHT) ||input->GetKey(KEY_INPUT_D)||
    input->GetButton(XINPUT_BUTTON_DPAD_RIGHT) || input->GetLeftStick().x > 0.5f)
{
    move += 1.0;
}


    // 左スティック
    //Vector2D stick = input->GetLeftStick();
    //if (stick.x > deadzone || stick.x < -deadzone)
    //{
    //    move = stick.x;
    //}

    ////  コントローラーボタン
    //if (input->GetButton(0))   
    //    move = -1.0f;

    //if (input->GetButton(1))   
    //    move = 1.0f;

    ////  キーボード
    //if (input->GetKey(KEY_INPUT_LEFT))
    //    move = -1.0f;

    //if (input->GetKey(KEY_INPUT_RIGHT))
    //    move = 1.0f;

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
