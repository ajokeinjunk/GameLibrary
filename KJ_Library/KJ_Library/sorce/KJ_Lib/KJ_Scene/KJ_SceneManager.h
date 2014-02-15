#ifndef H_K_SCENE_MANAGER_H
#define H_K_SCENE_MANAGER_H

namespace Klibrary{
	enum GameSceneState{
		START_UP = 0,
		DEMO,
		TITLE,
		MAIN,
		ENDING,
		TERMINATION,
	};

	class GameSceneManager{
	private:
		bool m_bMenu;

	public:
		GameSceneManager(){}
		~GameSceneManager(){}

	};
}

#endif