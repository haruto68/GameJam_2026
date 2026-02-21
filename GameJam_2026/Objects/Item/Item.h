#pragma once
#include "../GameObject.h"

class Item : public GameObject
{
private:
    float size = 40.0f; // 表示サイズ
    int makimono = 0;   // 巻物画像

public:
    Item();
    virtual ~Item();

    virtual void Initialize() override;
    virtual void Update(float delta_seconds) override;
    virtual void Draw(const Vector2D& screen_offset, bool flip_flag) const override;
    virtual void Finalize() override;

    virtual void OnHitCollision(GameObject* hit_object) override; // プレイヤーに拾われたときの処理用
};
