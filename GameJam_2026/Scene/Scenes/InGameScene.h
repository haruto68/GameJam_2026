#pragma once
#include"../SceneBase.h"
#include"../../Objects/GameObject.h"
#include"../../Objects/Character/Player/Player.h"
class InGameScene : public SceneBase
{
protected:

private:
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
};