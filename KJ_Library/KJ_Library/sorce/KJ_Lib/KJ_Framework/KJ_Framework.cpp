#include "KJ_Framework.h"
#include "../KJ_Mesh/KJ_BasicForm/KJ_BasicForm.h"
#include "../KJ_Renderer/KJ_Renderer.h"
#include "../KJ_System/KJ_RendererFactory.h"
#include "../KJ_Mesh/KJ_HardenedMesh/KJ_HardenedMesh.h"
#include "../KJ_Scene/AllScenes/TestScene.h"
#include "../KJ_Input/InputDeviceManager.h"


#pragma warning(disable:4482)

//========--------========--------========--------========--------========
//
//			GameFrameworkクラス
//
//========--------========--------========--------========--------========
namespace Klibrary{


	void GameFramework::GameBegin(){

		GameLoop();
	}

	GameFramework::GameFramework(){
		m_scene = nullptr;
	}

	GameFramework::~GameFramework(){
		Release();
	}


	HRESULT GameFramework::GameStartUp(){
		InputDeviceManager::Initialize();
		//最初に渡すシーン、描画デバイス設定を記述

		//RenderSystem::GetRenderer() = KrendererFactory::CreateRenderer(KrendererType::DirectX11);
		RenderSystem::Initialize();
		HRESULT result = RenderSystem::GetRenderer()->Initialize();

		if(m_scene != nullptr)m_scene->Initialize();


		return result;
	}

	void GameFramework::GameLoop(){
		//メッセージループ
		MSG msg = {0};

		while(msg.message != WM_QUIT){

			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}else{
				//アプリへの処理へ
				if(Update()){
					Render();
				}
			}

		}
	}

	bool GameFramework::Update(){
		InputDeviceManager::Update(SPF);
		if(m_scene != nullptr)m_scene->Update();

		return true;
	}

	void GameFramework::Render(){
		//レンダーの初めに画面初期化
		RenderSystem::GetRenderer()->BeginRender();
		
		if(m_scene != nullptr) m_scene->Render();
		

		//レンダー終りにSwapChain
		RenderSystem::GetRenderer()->EndRender();
	}

	bool GameFramework::ChangeScene(SCENE_STATE state){
		if(m_scene)SAFE_DELETE(m_scene);
		m_scene = new TestScene();
		m_scene->Initialize();
		return true;
	}

	bool GameFramework::ChangeSceneWhileLoading(SCENE_STATE state){
		if(m_scene)SAFE_DELETE(m_scene);
		return true;
	}

	void GameFramework::Release(){
		RenderSystem::Release();
		SAFE_DELETE(m_scene);
	}

} //namespace