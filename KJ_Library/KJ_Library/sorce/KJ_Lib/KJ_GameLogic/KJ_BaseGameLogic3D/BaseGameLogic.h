#pragma once

#include "../../KJ_Interface/KJ_Interface.h"
#include "../../KJ_Process/ProcessManager.h"
#include "../../KJ_Windows/KJ_WindowSystem.h"
#include "../../KJ_Actor/ActorFactory.h"

namespace Klibrary{
	/**
	* @brief BaseGameLogic�̃X�e�C�g�񋓌^
	* ���[�h���A���C�����j���[�A�J�n���v���C���[�ҋ@���A���[�r�[�A���ӊO�ƍׂ���
	*/
	enum BaseGameState
	{
		BaseGameState_Invalid,
		BaseGameState_Initializing,
		//BaseGameState_MainMenu,
		//BaseGameState_WaitingForPlayers,
		//BaseGameState_LoadingGameEnvironment,
		//BaseGameState_WaitingForPlayersToLoadEnvironment,
		//BaseGameState_SpawningPlayersActors,
		BaseGameState_Running
	};

	/*========--------========--------========--------========--------========--------========--------*/
	/*! @class BaseGameLogic
	    @brief ��{�I�ėp�I��GameLogic�N���X�B*/
	/*========--------========--------========--------========--------========--------========--------*/
	class BaseGameLogic : public IGameLogic{
	protected:
		//!< @brief  ���̃Q�[�������s����Ă���o�߂�������
		float                   m_LifeTime;   
		
		//!< @brief  GameLogic�̃v���Z�X�}�l�[�W���[
		ProcessManager* m_pProcessManager;
		//!< @brief  �A�v���P�[�V�������ɂP��WindowSystem
		WindowSystem2           m_WindowSystem;
		//!< @brief  Actor�Ǘ��p�}�b�v
		ActorMap                m_Actors;
		//!< @brief  �Q�[���̏��
		BaseGameState           m_GameState;
		//!< @brief  �Q�[���r���[�̃��X�g
		GameViewList            m_GameViewList;
		//!< @brief  �����A�N�^�[�𐶐����邽�߂̃t�@�N�g���[�N���X
		ActorFactory*           m_pActorFactory;

	public:
		BaseGameLogic();

		/**
		* @brief ������
		*/
		void VInitialize() override;
		/**
		* @brief �X�V
		* @param[in] elapsedTime ���܂ł̌o�ߎ���
		*/
		void VUpdate(float elapsedTime) override;
		/**
		* @brief �`��
		*/
		void VRender() override;
		/**
		* @brief �Q�[����ǂݍ���
		*/
		void VLoadGame(const std::string& resourceFile) override;
		/**
		* @brief �r���[�ǉ�
		* @param[in] view �ǉ�����view
		*/
		void AddView(shared_ptr<IGameView> view, ActorID actorID = INVALID_ACTOR_ID);
		/**
		/**
		* @brief �r���[���O
		*/
		void RemoveView(shared_ptr<IGameView> view);
		/**
		* @brief �A�N�^�[�쐬
		*/
		ActorSharedPtr VCreateActor(const ActorType& type) override;
		/**
		* @brief �A�N�^�[�p��
		*/
		void VDestroyActor(const ActorID actorID) override;
		/**
		* @brief �v���Z�X�ǉ�
		*/
		void AttachProcess(ProcessSharedPtr process){if(m_pProcessManager)m_pProcessManager->AttachProcesses(process);}
		/**
		* @brief �Q�[���X�e�C�g�ύX
		* @param[in] newState ���̐V�����Q�[���X�e�C�g����͂���B
		*/
		void VChangeGameState(enum BaseGameState newState);
		/**
		* @brief �J��
		*/
		void VRelease() override;

		//�Q�b�^�[
		const WindowSystem2& GetWindowSystem()const{ return m_WindowSystem; }
		ActorWeakPtr VGetActor(const ActorID actorID) override;
	};
}

