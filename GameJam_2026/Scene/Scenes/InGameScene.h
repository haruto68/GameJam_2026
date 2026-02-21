#pragma once
#include"../SceneBase.h"
#include"../../Objects/GameObject.h"
#include"../../Objects/Character/Player/Player.h"
#include"../../Objects/Ball/Ball.h"
#include "../../Objects/Block/Block.h"
#include "../../Objects/Block/Block2.h"
#include <vector>

//std::vector<Block*> blocks;
class InGameScene : public SceneBase
{
protected:

private:
	int score = 0;		//スコア
	int item = 0;		//獲得アイテム数
	int mato[3] = {};	//壊したマト数

	int have_ball = 3;
	int screen_ball = 1;

	bool next_scene = false;
	float next_count = 0.0f;

public:
	std::vector<GameObject*> scene_objects_list;//オブジェクトリスト
	class GameObjectManager* object_manager;    //オブジェクトマネージャーインスタンス
	class Player* player;                        //プレイヤーインスタンス

public:
	InGameScene();
	~InGameScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

	void Animation(const float& delta_second);


	void ObjectListLoop(const float& delta_second);	//オブジェクトリストループ
};