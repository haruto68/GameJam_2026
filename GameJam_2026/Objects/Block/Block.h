#pragma once
#include "../GameObject.h"

class Block : public GameObject
{
private:
    Vector2D size;

public:
    Block(/*const Vector2D& pos*/);  
    virtual ~Block();

    virtual void Initialize() override;
    virtual void Update(float) override;
    virtual void Draw(const Vector2D&, bool) const override;
    virtual void Finalize() override;
};
