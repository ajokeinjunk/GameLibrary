#ifndef H_KLIB_TEST_SCENE_H
#define H_KLIB_TEST_SCENE_H

#include "../../KJ_library.h"

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