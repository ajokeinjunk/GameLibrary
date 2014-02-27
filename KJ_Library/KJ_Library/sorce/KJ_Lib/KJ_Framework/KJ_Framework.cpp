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
//			GameFramework�N���X
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
		//�ŏ��ɓn���V�[���A�`��f�o�C�X�ݒ���L�q

		//RenderSystem::GetRenderer() = KrendererFactory::CreateRenderer(KrendererType::DirectX11);
		RenderSystem::Initialize();
		HRESULT result = RenderSystem::GetRenderer()->Initialize();

		if(m_scene != nullptr)m_scene->Initialize();


		return result;
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
		if(m_scene != nullptr)m_scene->Update();

		return true;
	}

	void GameFramework::Render(){
		//�����_�[�̏��߂ɉ�ʏ�����
		RenderSystem::GetRenderer()->BeginRender();
		
		if(m_scene != nullptr) m_scene->Render();
		

		//�����_�[�I���SwapChain
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