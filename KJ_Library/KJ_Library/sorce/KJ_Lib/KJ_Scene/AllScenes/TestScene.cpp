#include "TestScene.h"

#include <assert.h>

namespace Klibrary{

	using namespace std;

	//========--------========--------========--------========--------========
	//
	//			TestSceneƒNƒ‰ƒX
	//
	//========--------========--------========--------========--------========
	bool TestScene::Initialize()
	{
		if(m_IsInitialized == false){
			bool success = false;

			InputDeviceManager::EnableMouse();

			CameraSharedPtr camera = make_shared<Camera>();
			FBXLoader loader;
			loader.InitializeLoader();
			success = loader.LoadScene("cameraText.fbx");

			AnimationCamera motionCam;
			loader.LoadCameraAnimation(motionCam);
			
			loader.LoadCamera(camera);
			
			camera->SetFoV(0.785398185f);
			camera->SetCameraInfoID(99);

			CameraManager::AddCamera(camera);
			CameraManager::SetActiveCamera(99);

			//gMQO = new KJ_HardenedMesh();
			//gMQO->Initialize();
			//gMQO->LoadHardenedMesh("DATA\\sabo\\sabo.mqo");
			//gMQO->SetScale(1.01f);

			gMQOTube = new KJ_HardenedMesh();
			gMQOTube->Initialize();
			gMQOTube->LoadHardenedMesh("DATA\\sabo\\testTube.mqo");
			gMQOTube->SetScale(0.01f);
			gMQOTube->SetPosition(0.0f, 0.0f, 0.0f);

			board = new KJ_BaseFormMesh();
			board->Initialize();
			board->MakePlane(100, 100, 100);
			board->SetPosition(0, -3.0f, 0);
			board->Update();

			light = new DirectionalLight(Vector3(1, 1, -3));

			

			m_IsInitialized = true;
		}

		return true;
	}

	void TestScene::Update()
	{
		static  float s = 0;
		s += 0.003f;
		float sin = sinf(s);

		sin = sin*0.5f + 0.5f;

		//gMQO->SetAngle(s);
		//gMQO->SetPosition(Vector3(0,sin,0));
		//gMQO->Update();

		gMQOTube->SetAngle(s);
		gMQOTube->Update();


		ColorF color = { 1.0f, 1.0f, 1.0f, 1.0f };
		light->SetColor(color);

		CameraManager::Update(SPF);
	}

	void TestScene::Render()
	{
		CameraManager::ClearTargetView();
		CameraManager::Activate();

		light->VLocate();

		//gMQO->Render();
		gMQOTube->Render();
		//board->Render();
	}

	void TestScene::Release(){
		SAFE_DELETE(gMQO);
		SAFE_DELETE(gMQOTube);
		SAFE_DELETE(light);
		SAFE_DELETE(board);
		CameraManager::Release();
	}
}