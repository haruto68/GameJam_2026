#include"SceneFactory.h"
#include"SceneBase.h"

#include"Scenes/TitleScene.h"
#include"Scenes/HelpScene.h"
#include"Scenes/InGameScene.h"
#include"Scenes/ResultScene.h"
#include"Scenes/RankingScene.h"
#include"Scenes/CreditScene.h"

SceneBase* SceneFactory::CreateScene(eSceneType scene)
{
	switch (scene)
	{
	case eSceneType::eTitle:
		return new TitleScene();
		break;
	case eSceneType::eHelp:
		return new HelpScene();
		break;
	case eSceneType::eInGame:
		return new InGameScene();
		break;
	case eSceneType::eResult:
		return new ResultScene();
		break;
	case eSceneType::eRanking:
		return new RankingScene();
		break;
	case eSceneType::eExit:
		break;
	case eSceneType::eCreditScene:
		return new CreditScene();
		break;
	default:
		break;
	}
	return nullptr;
}