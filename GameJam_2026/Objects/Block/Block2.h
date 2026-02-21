#pragma once
#include "../GameObject.h"

class Block2 : public GameObject
{
private:
    Vector2D size;
    bool item_spawned = false;
    bool death_flag = false;
    float anime_time = 0.0f;
    int anime_num = 0;
    int mato_image[6];
    int maruta_image[4];

public:
    Block2(/*const Vector2D& pos*/);
    virtual ~Block2();

    virtual void Initialize() override;
    virtual void Update(float) override;
    virtual void Draw(const Vector2D&, bool) const override;
    virtual void Finalize() override;

    virtual void OnHitCollision(GameObject* hit_object) override; // Õ“Ëˆ—
public:
    void Animation(float);
};

