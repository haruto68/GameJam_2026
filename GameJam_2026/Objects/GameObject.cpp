#include"DxLib.h"
#include"GameObject.h"
#include"GameObjectManager.h"

GameObject::GameObject()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

}

GameObject::~GameObject()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void GameObject::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void GameObject::Update(float delta_second)
{

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset">オフセット値</param>
void GameObject::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	
}

/// <summary>
/// 終了時処理
/// </summary>
void GameObject::Finalize()
{

}

//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{

}

float GameObject::GetHp()
{
	return this->hp;
}
void GameObject::SetHp(float h)
{
	this->hp = h;
}

//座標取得処理
const Vector2D& GameObject::GetLocation() const
{
	return location;
}

//座標設定処理
void GameObject::SetLocation(const Vector2D location)
{
	this->location = location;
}

const Vector2D& GameObject::GetVelocity() const
{
	return this->velocity;
}

void GameObject::SetVelocity(const Vector2D velocity)
{
	this->velocity = velocity;
}

//コリジョン取得処理
const Collision& GameObject::GetCollision() const
{
	return collision;
}

//レイヤー取得処理
const unsigned char GameObject::GetZLayer() const
{
	return z_layer;
}

//可動性取得処理
const bool GameObject::GetMobility() const
{
	return is_mobility;
}

//プレイヤー座標設定処理
void GameObject::SetPlayerLocation(Vector2D location)
{
	if (player_location.x == 0.0f && player_location.y == 0.0f)
	{
		old_player_location = location;
	}
	player_location = location;
}

//プレイヤーステータス設定処理
void GameObject::SetPlayerStats(PlayerStats stats)
{
	player_stats = stats;
}


//AがBを追尾する処理
Vector2D GameObject::Tracking(Vector2D A, Vector2D B)
{
	Vector2D velocity;	//加速度
	float distance;		//距離

	velocity.x = A.x - B.x;
	velocity.y = A.y - B.y;

	distance = sqrt(pow(velocity.x, 2.0) + pow(velocity.y, 2.0));

	velocity.x /= distance;
	velocity.y /= distance;

	velocity *= -1;

	return velocity;

}

//インスタンス確認処理
const GameObjectManager* GameObject::CheckInstance() const
{
	return object_manager;
}

//インスタンス設定処理
void GameObject::SetInstance(GameObjectManager* instance)
{
	object_manager = instance;
}