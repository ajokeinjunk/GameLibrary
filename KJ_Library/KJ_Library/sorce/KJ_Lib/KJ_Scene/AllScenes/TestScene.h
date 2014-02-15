#ifndef H_KLIB_TEST_SCENE_H
#define H_KLIB_TEST_SCENE_H

#include "../KJ_BaseScene.h"
#include "../../KJ_System/KJ_System.h"
#include "../../KJ_Mesh/KJ_HardenedMesh/KJ_HardenedMesh.h"
#include "../../KJ_Camera/KJ_Camera.h"
#include "../../KJ_Light/Light.h"
#include "../../KJ_Mesh/KJ_BasicForm/KJ_BasicForm.h"

namespace Klibrary{


	class TestScene : public BaseScene{
	private:
		KJ_HardenedMesh* gMQO;
		KJ_HardenedMesh* gMQOTube;

		DirectionalLight* light;
		KJ_BaseFormMesh* board;

	public:
		TestScene() :gMQO(nullptr),  board(nullptr), light(nullptr){}
		~TestScene(){ Release(); }

		bool Initialize();
		void Update();
		void Render();
		void Release();
	};
}

#endif