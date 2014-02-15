#ifndef H_KLIB_SCENE_SYSTEM_H
#define H_KLIB_SCENE_SYSTEM_H
#include "KJ_BaseScene.h"
#include <unordered_map>

namespace Klibrary{
	using namespace std;


	enum SCENE_STATE{
		TITLE = 0,
		MOVIE,
		TEST1,
		STAGE1,
		ENDING,
	};

	class SceneFactory{
	private:


	public:
		unordered_map<string, int, string> hash;  //lol 3î‘ñ⁄ÇÃÉLÅ[ÇÕàÍëÃÇ»ÇÒÇ»ÇÃÇ©ÅB
		static BaseScene* CreateScene(SCENE_STATE state);
	};

}
#endif