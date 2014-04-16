#pragma once

/******************************************************************************/
/*! @addtogroup ���W���[����_�T�u���W���[����
@file       KJ_Framework.h
@brief      �t�@�C���̊T�v
*******************************************************************************
�t�@�C���̏ڍׂȐ���
*******************************************************************************
@date       �쐬��(YYYY/MM/DD)
@author     �쐬�Җ�
@par        Revision
$Id$
@par        Copyright
20XX-20XX ABC Company Co., Ltd. All rights reserved.
*******************************************************************************
@par        History
- 20XX/01/01 �X�V�Җ�1
-# Initial Version
- 20XX/01/02 �X�V�Җ�2
-# Add xxx function
-# Delete yyy function
******************************************************************************/

/*! @ingroup ���W���[����_�T�u���W���[���� */
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
	    @brief �Q�[���̌^�g�������N���X�B\n
	    Windows����̃G���g���[�|�C���g�ƂȂ�A\n
	    ���̒���GameLogic���܂ޑS�ẴQ�[�����삪�s����B*/
	/*========--------========--------========--------========--------========--------========--------*/
	class BaseGameFramework{
	protected:
		//!< @brief �E�B���h�E�Ɋւ�����\����
		WindowSystem2 m_WindowSystem;
		//!< @brief �t���[�����[�N�̃X�e�C�g
		FrameworkState m_FrameworkState;
		//!< @brief �Q�[���̍\��
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

		//�Q�b�^�[
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
		* @brief ���[�f�B���O������Ŏ��̃V�[�������[�f�B���O����B
		*/
		bool ChangeSceneWhileLoading(SCENE_STATE state);
		bool ChangeScene(SCENE_STATE state);
		bool ChangeScene(char* sceneName);

		void Release();
	};

} //Klibrary

/* @} */