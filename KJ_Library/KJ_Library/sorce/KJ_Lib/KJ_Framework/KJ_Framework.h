#pragma once

/******************************************************************************/
/*! @addtogroup モジュール名_サブモジュール名
@file       KJ_Framework.h
@brief      ファイルの概要
*******************************************************************************
ファイルの詳細な説明
*******************************************************************************
@date       作成日(YYYY/MM/DD)
@author     作成者名
@par        Revision
$Id$
@par        Copyright
20XX-20XX ABC Company Co., Ltd. All rights reserved.
*******************************************************************************
@par        History
- 20XX/01/01 更新者名1
-# Initial Version
- 20XX/01/02 更新者名2
-# Add xxx function
-# Delete yyy function
******************************************************************************/

/*! @ingroup モジュール名_サブモジュール名 */
/* @{ */

#include <Windows.h>
#include <memory>

#include "..\KJ_Renderer\KJ_DirectX\KJ_DirectX3D.h"
#include "../KJ_Camera/KJ_Camera.h"
#include "../KJ_Scene/KJ_BaseScene.h"
#include "../KJ_Scene/KJ_SceneSystem.h"
#include "../KJ_GameLogic/KJ_BaseGameLogic3D/BaseGameLogic.h"

namespace Klibrary{
	class GameFramework;

	typedef shared_ptr<GameFramework> FrameworkSharedPtr;
	typedef weak_ptr<GameFramework> FrameworkWeakPtr;

	enum FrameworkState{
		FRAMEWORK_INITIALIZING = 0,
		FRAMEWORK_RUNNING,
		FRAMEWORK_QUITE_REQUESTED,
		FRAMEWORK_QUITTING,
	};

	/*========--------========--------========--------========--------========--------========--------*/
	/*! @class BaseGameFramework
	    @brief ゲームの型枠を扱うクラス。\n
	    Windowsからのエントリーポイントとなり、\n
	    この中でGameLogicを含む全てのゲーム動作が行われる。*/
	/*========--------========--------========--------========--------========--------========--------*/
	class BaseGameFramework{
	protected:
		//!< @brief ウィンドウに関する情報構造体
		WindowSystem2 m_WindowSystem;
		//!< @brief フレームワークのステイト
		FrameworkState m_FrameworkState;
		//!< @brief ゲームの構成
		BaseGameLogic* m_pGameLogic;

		HRESULT GameStartUp();
		bool GameLoop();
		bool Update();
		void Render();

		BaseGameLogic* CreateGame();
	public:
		BaseGameFramework();
		~BaseGameFramework();

		void GameBegin();

		void Release();

		//ゲッター
		const WindowSystem2& GetWindowSystem()const{ return m_WindowSystem; }
	};

	class GameFramework{
	private:
		SceneSharedPtr m_pScene;
		BaseGameLogic* m_pGameLogic;
		
		void GameLoop();
		bool Update();
		void Render();

	public:
		GameFramework();
		~GameFramework();

		HRESULT GameStartUp();
		void GameBegin();

		/**
		* @brief ローディングを挟んで次のシーンをローディングする。
		*/
		bool ChangeSceneWhileLoading(SCENE_STATE state);
		bool ChangeScene(SCENE_STATE state);
		bool ChangeScene(char* sceneName);

		void Release();
	};

} //Klibrary

/* @} */