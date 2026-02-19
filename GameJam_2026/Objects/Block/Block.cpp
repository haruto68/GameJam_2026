#include "Block.h"
#include "DxLib.h"

Block::Block(/*const Vector2D& pos*/)
{
    //location = pos;
    size = Vector2D(100.0f, 30.0f);

    collision.box_size = size;
    collision.is_blocking = true;

    z_layer = 1;
    is_mobility = false;
}

Block::~Block()
{
}

void Block::Initialize()
{
}

void Block::Update(float)
{
}

void Block::Draw(const Vector2D&, bool) const
{
    float halfW = size.x * 0.5f;
    float halfH = size.y * 0.5f;

    DrawBox(
        (int)(location.x - halfW),
        (int)(location.y - halfH),
        (int)(location.x + halfW),
        (int)(location.y + halfH),
        GetColor(0, 200, 255),
        TRUE
    );
}

void Block::Finalize()
{
}
