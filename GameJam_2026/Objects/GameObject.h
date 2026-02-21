#pragma once

#include"Collision.h"
#include"Character/Player/PlayerStats.h"

class GameObject
{
protected:
	// オブジェクトマネージャーのインスタンス
	class GameObjectManager* object_manager;

	Vector2D location;				//座標
	Vector2D velocity = 0;
	Collision collision;			//コリジョン
	int image;						//画像
	int transparency;				//透明度
	unsigned char z_layer;			//レイヤー
	bool is_mobility;				//可動性
	Vector2D player_velocity;		//プレイヤー加速度
	Vector2D player_location;		//プレイヤー座標
	Vector2D old_player_location;	//生成時プレイヤー座標
	PlayerStats player_stats;		//プレイヤーステータス
	float hp;						//HP

public:
	GameObject();
	~GameObject();

public:
	virtual void Initialize();
	virtual void Update(float);
	virtual void Draw(const Vector2D&, bool) const;
	virtual void Finalize();

	virtual void OnHitCollision(GameObject*);		//当たり判定通知処理

	float GetHp();									//HP取得処理
	void SetHp(float);								//HP設定処理

	const Vector2D& GetLocation() const;			//座標取得処理
	void SetLocation(const Vector2D);				//座標設定処理

	const Vector2D& GetVelocity() const;
	void SetVelocity(const Vector2D);

	const Collision& GetCollision() const;			//コリジョン取得処理
	const unsigned char GetZLayer() const;			//レイヤー取得処理
	const bool GetMobility() const;					//可動性取得処理

	void SetPlayerVelocity(Vector2D location);		//プレイヤー座標設定処理
	void SetPlayerLocation(Vector2D location);		//プレイヤー座標設定処理
	void SetPlayerStats(PlayerStats stats);			//プレイヤーステータス設定処理
	Vector2D Tracking(Vector2D A, Vector2D B);		//AがBを追尾する処理
	Vector2D Calc_Distance(Vector2D A, Vector2D B);	//AからBまでの距離を計算する処理

	const GameObjectManager* CheckInstance() const;	//インスタンス確認処理
	void SetInstance(GameObjectManager* instance);	//インスタンス設定処理

};