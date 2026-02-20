#include "Player.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/UserTemplate.h"
#include "../../../Objects/Item/Item.h"
#include "../../../Objects/Ball/Ball.h"
#include "../../../Objects/GameObject.h"
#include "DxLib.h"

// ゲージ関連定数
constexpr int GAUGE_WIDTH = 200;
constexpr int GAUGE_HEIGHT = 20;
constexpr int GAUGE_MARGIN = 30;

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

// アイテムを取得
void Player::AddItem()
{
    item_count++;
}

void Player::Update(float delta_seconds)
{
    Movement(delta_seconds);

    // 色タイマー更新
    if (color_timer > 0.0f)
        color_timer -= delta_seconds;

    // 入力更新
    InputManager* input = InputManager::GetInstance();

    //入力情報の更新
    input->Update();

    // クールタイム管理
    if (attack_cool > 0)
        attack_cool -= delta_seconds;
    else
        attack_cool = 0.0f;


    // collision.is_blocking = false;
    // アタックL
    if ((input->GetKey(KEY_INPUT_J) || input->GetButton(XINPUT_BUTTON_LEFT_SHOULDER))
        && attack_cool <= 0.0f)
    {
        attack_cool = 1.0f;
        object_manager->CreateGameObject<Attack_L>(Vector2D(location.x, location.y - 40.0f));
    }

    // アタックR
    if ((input->GetKey(KEY_INPUT_K) || input->GetButton(XINPUT_BUTTON_RIGHT_SHOULDER))
        && attack_cool <= 0.0f)
    {
        attack_cool = 1.0f;
        object_manager->CreateGameObject<Attack_R>(Vector2D(location.x, location.y - 40.0f));
    }

    // 貫通弾管理
    if (is_special_active)
    {
        special_timer -= delta_seconds;

        if (special_timer <= 0.0f)
        {
            is_special_active = false;
    }
    }

    // 全ボールに反映
    Ball::is_penetrating = is_special_active;



}

void Player::Draw(const Vector2D&, bool) const
{
    float halfW = collision.box_size.x * 0.5f;
    float halfH = collision.box_size.y * 0.5f;

    int r = 255, g = 255, b = 255;
    if (is_special_active)
        r = 255, g = 0, b = 0;

    // プレイヤー描画
    DrawBox(
        (int)(location.x - halfW),
        (int)(location.y - halfH),
        (int)(location.x + halfW),
        (int)(location.y + halfH),
        GetColor(r, g, b),
        TRUE
    );

    // ゲージ描画
    int x1 = D_WIN_MAX_X - GAUGE_MARGIN - GAUGE_WIDTH;
    int y1 = GAUGE_MARGIN;
    int x2 = D_WIN_MAX_X - GAUGE_MARGIN;
    int y2 = GAUGE_MARGIN + GAUGE_HEIGHT;

    // 背景
    DrawBox(x1, y1, x2, y2, GetColor(50, 50, 50), TRUE);

    // ゲージ割合
    float rate = is_special_active ? special_timer / 3.0f : item_count / 2.0f;
    if (rate > 1.0f) rate = 1.0f;
    if (rate < 0.0f) rate = 0.0f;

    // ゲージ本体
    DrawBox(x1, y1, x1 + (int)(GAUGE_WIDTH * rate), y2, GetColor(255, 0, 0), TRUE);

    // 枠
    DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), FALSE);

    // 縦線（プレイヤー可動制限）
    DrawLine(x1, 0, x1, D_WIN_MAX_Y, GetColor(255, 255, 255));
}

void Player::Movement(float delta_seconds)
{
    const float speed = 600.0f;
    /*const float deadzone = 0.2f;*/

    //入力機能インスタンス取得
    InputManager* input = InputManager::GetInstance();

    //入力情報の更新
    input->Update();

    float move = 0.0f;
    if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_A) ||
        input->GetButton(XINPUT_BUTTON_DPAD_LEFT) || input->GetLeftStick().x < -0.5f)
        move -= 1.0f;

    //右移動
    if (input->GetKey(KEY_INPUT_RIGHT) || input->GetKey(KEY_INPUT_D) ||
        input->GetButton(XINPUT_BUTTON_DPAD_RIGHT) || input->GetLeftStick().x > 0.5f)
        move += 1.0f;

    // アイテム使用
    if (!is_special_active && item_count >= 2 && input->GetButton(XINPUT_BUTTON_A))
    {
        is_special_active = true;
        special_timer = 3.0f;
        item_count = 0;
    }
    



    // 移動
    location.x += move * speed * delta_seconds;

    // 画面端制限（右端はゲージ左端まで）
    float half = collision.box_size.x * 0.5f;
    float gauge_left = D_WIN_MAX_X - GAUGE_MARGIN - GAUGE_WIDTH;

    if (location.x - half < 0.0f) location.x = half;
    if (location.x + half > gauge_left) location.x = gauge_left - half;
}

void Player::ChangeColorTemporarily(int r, int g, int b)
{
    color_r = r;
    color_g = g;
    color_b = b;
    color_timer = 2.0f;
}

void Player::Finalize()
{
}

void Player::OnHitCollision(GameObject*)
{
}
