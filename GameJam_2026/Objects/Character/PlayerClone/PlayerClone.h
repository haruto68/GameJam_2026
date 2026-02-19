// PlayerClone.h
#pragma once
#include "../../../Objects/Character/Player/Player.h"
#include "../../../Utility/Vector2D.h"
#include <cmath> // sin関数用

class PlayerClone : public Player
{
private:
    float life_time = 5.0f;        // クローンの寿命（秒）
    Vector2D start_location;       // 初期位置保持
    float move_direction = 1.0f;   // 左右移動方向
    float speed = 300.0f;          // 移動速度
    float move_range = 200.0f;     // 初期位置からの移動幅

public:
    PlayerClone();
    virtual ~PlayerClone();

    virtual void Initialize() override;
    virtual void Update(float delta_seconds) override;
    virtual void Draw(const Vector2D&, bool) const override;
};
