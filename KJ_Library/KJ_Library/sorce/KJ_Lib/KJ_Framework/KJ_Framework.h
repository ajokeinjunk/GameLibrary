#ifndef H_K_FRAMEWORK_H
#define H_K_FRAMEWORK_H

#include <Windows.h>
#include <memory>

#include "..\KJ_Renderer\KJ_DirectX\KJ_DirectX3D.h"
#include "../KJ_Camera/KJ_Camera.h"
#include "../KJ_Scene/KJ_BaseScene.h"
#include "../KJ_Scene/KJ_SceneSystem.h"

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			GameFrameworkƒNƒ‰ƒX
	//
	//========--------========--------========--------========--------========
	class GameFramework;

	typedef shared_ptr<GameFramework> FrameworkSharedPtr;
	typedef weak_ptr<GameFramework> FrameworkWeakPtr;


	class GameFramework{
	private:
		BaseScene* m_scene;
		
		void GameLoop();
		void Initialize();
		bool Update();
		void Render();

	public:
		GameFramework();
		~GameFramework();

		HRESULT GameStartUp();
		void GameBegin();

		bool ChangeSceneWhileLoading(SCENE_STATE state);
		bool ChangeScene(SCENE_STATE state);
		bool ChangeScene(char* sceneName);

		void Release();
	};

} //Klibrary

#endif