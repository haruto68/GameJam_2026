
#pragma once
#include "../GameObject.h"
#include "../../Objects/Character/Player/Player.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Utility/Vector2D.h"

class Item_BallUp : public GameObject
{
private:
    float size = 40.0f; // 表示サイズ
    int image_handle = 0; // 画像ハンドル（必要なら）

public:
    Item_BallUp();
    virtual ~Item_BallUp();

    virtual void Initialize() override;
    virtual void Update(float delta_seconds) override;
    virtual void Draw(const Vector2D& screen_offset, bool flip_flag) const override;
    virtual void Finalize() override;

    virtual void OnHitCollision(GameObject* hit_object) override;
};