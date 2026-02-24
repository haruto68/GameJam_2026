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
	int backgound_UI = 0;	// UI背景
	int background;

	int numbers_image[11] = {};	//数字画像
	int draw_number[5] = { 10,10,10,10,10 };	//数字引数
	int syuriken = 0;		//手裏剣

	int score = 0;			//スコア
	int item = 0;			//獲得アイテム数
	int mato[3] = {};		//壊したマト数

	int have_ball = 3;		//所持中の手裏剣
	int screen_ball = 0;	//画面内の手裏剣

	int screen_block1 = 0;	//画面内のブロック1

	bool next_scene = false;
	float next_count = 0.0f;

	int main_handle;

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

	void CreateBlock1();		//ブロック1生成
};