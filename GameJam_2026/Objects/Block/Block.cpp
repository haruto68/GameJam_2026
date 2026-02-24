#include "Block.h"
#include "DxLib.h"
#include"../../Objects/GameObjectManager.h"
#include"../../Objects/Item/Item.h"
#include"../../Objects/Item/Item_BallUp.h"
#include"../../Objects/Block/Block2.h"


Block::Block(/*const Vector2D& pos*/): break_se(-1)
{
    size = Vector2D(100.0f, 50.0f);

    //location = pos;
    size = Vector2D(100.0f, 50.0f);

    collision.box_size = size;
    collision.is_blocking = true;
    collision.object_type = eObjectType::eBlock;
    collision.hit_object_type.push_back(eObjectType::eBall);

    ResourceManager* rm = ResourceManager::GetInstance();

    mato_image[0] = rm->GetImages("Resource/Images/mato1.png")[0];
    mato_image[1] = rm->GetImages("Resource/Images/mato2.png")[0];
    mato_image[2] = rm->GetImages("Resource/Images/mato3.png")[0];
    mato_image[3] = rm->GetImages("Resource/Images/mato4.png")[0];
    mato_image[4] = rm->GetImages("Resource/Images/mato5.png")[0];
    mato_image[5] = rm->GetImages("Resource/Images/mato6.png")[0];

    maruta_image[0] = rm->GetImages("Resource/Images/maruta1.png")[0];
    maruta_image[1] = rm->GetImages("Resource/Images/maruta2.png")[0];
    maruta_image[2] = rm->GetImages("Resource/Images/maruta3.png")[0];
    maruta_image[3] = rm->GetImages("Resource/Images/maruta4.png")[0];

    break_se=rm->GetSounds("Resource/sound/isi.mp3");

    image = maruta_image[0];

    z_layer = 1;
    is_mobility = false;
}

Block::~Block()
{
}

void Block::Initialize()
{
    hp = 100;

    intial_location = location;
}

void Block::Update(float delta_seconds)
{
    Movement(delta_seconds);
    Animation(delta_seconds);
}


void Block::Draw(const Vector2D&, bool) const
{
    float halfW = size.x * 0.5f;
    float halfH = size.y * 0.5f;

    /*DrawBox(
        (int)(location.x - halfW),
        (int)(location.y - halfH),
        (int)(location.x + halfW),
        (int)(location.y + halfH),
        GetColor(0, 200, 255),
        TRUE
    );*/

    //DrawRotaGraphF(location.x, location.y, 0.3, 0.0, image, true, FALSE);
    DrawRotaGraphF(location.x, location.y, 0.6, 0.0, image, true, FALSE); 
    
    /*DrawBoxAA(location.x - halfW, location.y - halfH, location.x + halfW, location.y + halfH,
        GetColor(0, 0, 255), false);*/

}

void Block::Finalize()
{
}

void Block::OnHitCollision(GameObject* hit_object)
{
    // 衝突対象が Ball の場合
    if (hit_object->GetCollision().object_type == eObjectType::eBall)
    {

        if (death_flag == false)
        {
            death_flag = true;
            collision.is_blocking = false;

            PlaySoundMem(break_se, DX_PLAYTYPE_BACK); 
        }

        GameObject* obj = nullptr;

        // まだアイテム生成していなければ
        if (!item_spawned)
        {
            item_spawned = true; // フラグを先に立てる → 安全

            if (object_manager)
            {
                int r = rand() % 100; //
                if (r < 15)
                {
                    // 1/10 の確率で分身アイテム
                    object_manager->CreateGameObject<Item>(location);
                }
                else if (r < 30)
                {
                    // 1/10 の確率でボール増加アイテム
                    object_manager->CreateGameObject<Item_BallUp>(location);
                }
                else if (r < 33)
                {
                    //obj = object_manager->CreateGameObject<Block2>(Vector2D(0, 350));
                    //obj->SetVelocity(Vector2D(1.0f, 0.0f));
                }
            }
        }

    }
}

void Block::Movement(float delta_seconds)
{
    if (location.y < intial_location.y + 400.0f)
    {
        float speed = 300.0f;
        location += velocity * speed * delta_seconds;
    }
}

void Block::Animation(float delta_seconds)
{
    if (death_flag == true)
    {
        anime_time += delta_seconds;
    }

    if (anime_time >= 0.05f)
    {
        anime_time = 0.0f;
        anime_num++;

        /*if (anime_num > 5)
        {
            if (object_manager)
            {
                object_manager->DestroyGameObject(this);
            }
        }
        image = mato_image[anime_num];*/

        if (anime_num > 3)
        {
            if (object_manager)
            {
                object_manager->DestroyGameObject(this);
            }
        }
        image = maruta_image[anime_num];

    }
}

void Block::Break()
{
    if (death_flag == false)
    {
        death_flag = true;
        collision.is_blocking = false;
    }
}