#include "KJ_SceneSystem.h"
#include "AllScenes\TestScene.h"

#pragma warning(disable : 4482)

namespace Klibrary{

	BaseScene* SceneFactory::CreateScene(SCENE_STATE state){
		switch (state)
		{
		case SCENE_STATE::TITLE:
			return nullptr;

		case SCENE_STATE::MOVIE:
			return nullptr;

		case SCENE_STATE::STAGE1:
			return nullptr;

		case SCENE_STATE::ENDING:
			return nullptr;

		case SCENE_STATE::TEST1:
			return new TestScene();

		default:
			return nullptr;
		}
	}

}