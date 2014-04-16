#include "KJ_Framework.h"
#include "../KJ_Mesh/KJ_BasicForm/KJ_BasicForm.h"
#include "../KJ_Renderer/KJ_Renderer.h"
#include "../KJ_System/KJ_RendererFactory.h"
#include "../KJ_Mesh/KJ_HardenedMesh/KJ_HardenedMesh.h"
#include "../KJ_Scene/AllScenes/TestScene.h"
#include "../KJ_Input/InputDeviceManager.h"

#pragma warning(disable:4482)

namespace Klibrary{

	//========--------========--------========--------========--------========
	//
	//			BaseGameFramework�N���X
	//
	//========--------========--------========--------========--------========
	BaseGameFramework::BaseGameFramework(){
		m_pGameLogic = nullptr;
	}

	BaseGameFramework::~BaseGameFramework(){
		Release();
	}

	void BaseGameFramework::GameBegin(){
		GameStartUp();
		GameLoop();
	}

	HRESULT BaseGameFramework::GameStartUp(){
		//�������������L�q
		//GameLogic�ݒ�
		//�ŏ����ɐݒ肷��View�Ȃǂ��ݒ肷��
		InputDeviceManager::Initialize();
		RenderSystem::Initialize();
		m_pGameLogic = CreateGame();

		return S_OK;
	}

	bool BaseGameFramework::GameLoop(){
		//���b�Z�[�W���[�v
		MSG msg = { 0 };

		while (msg.message != WM_QUIT){

			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else{
				//�A�v���ւ̏���
				if (Update()){
					Render();
				}
			}
		}


		return true;
	}
	BaseGameLogic* BaseGameFramework::CreateGame(){
		BaseGameLogic* gameLogic = nullptr;
		gameLogic = new BaseGameLogic();
		gameLogic->VInitialize();

		return gameLogic;
	}


	bool BaseGameFramework::Update(){

		InputDeviceManager::Update(SPF);
		int time = timeGetTime();
		time = time;
		//m_pGameLogic->VUpdate();
		return true;
	}

	void BaseGameFramework::Render(){
		m_pGameLogic->VRender();
	}

	void BaseGameFramework::Release(){
		RenderSystem::Release();
		SAFE_DELETE(m_pGameLogic);
	}


	//========--------========--------========--------========--------========
	//
	//			GameFramework�N���X
	//
	//========--------========--------========--------========--------========
	void GameFramework::GameBegin(){
		GameLoop();
	}

	GameFramework::GameFramework(){
		m_pGameLogic = nullptr;
	}

	GameFramework::~GameFramework(){
		Release();

	}


	HRESULT GameFramework::GameStartUp(){
		InputDeviceManager::Initialize();
		//�ŏ��ɓn���V�[���A�`��f�o�C�X�ݒ���L�q

		//RenderSystem::GetRenderer() = KrendererFactory::CreateRenderer(KrendererType::DirectX11);
		RenderSystem::Initialize();

		if(m_pScene.get() != nullptr)m_pScene->Initialize();

		return S_OK;
	}

	void GameFramework::GameLoop(){
		//���b�Z�[�W���[�v
		MSG msg = {0};

		while(msg.message != WM_QUIT){

			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}else{
				//�A�v���ւ̏�����
				if(Update()){
					Render();
				}
			}

		}
	}

	bool GameFramework::Update(){
		InputDeviceManager::Update(SPF);
		if (m_pScene.get() != nullptr)m_pScene->Update();

		return true;
	}

	void GameFramework::Render(){
		//�����_�[�̏��߂ɉ�ʏ�����
		RenderSystem::GetRenderer()->PreRender();
		
		if (m_pScene.get() != nullptr) m_pScene->Render();
		

		//�����_�[�I���SwapChain
		RenderSystem::GetRenderer()->PostRender();
	}

	bool GameFramework::ChangeScene(SCENE_STATE state){
		m_pScene = std::make_shared<TestScene>();
		m_pScene->Initialize();
		return true;
	}

	bool GameFramework::ChangeSceneWhileLoading(SCENE_STATE state){
		return true;
	}

	void GameFramework::Release(){
		RenderSystem::Release();
		SAFE_DELETE(m_pGameLogic);
	}

} //namespace