#pragma once

#include "../../KJ_Interface/KJ_Interface.h"
#include "../../KJ_Process/ProcessManager.h"

namespace Klibrary{
	/**
	* @brief BaseGameLogic�̃X�e�C�g�񋓌^
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

	/** ===================================================================================
	* @class BaseGameLogic
	* @brief ��{�I�ėp�I��GameLogic�N���X�B
	==================================================================================== */
	class BaseGameLogic : public IGameLogic{
	protected:
		//!< @brief  ���̃Q�[�������s����Ă���o�߂�������
		float                   m_LifeTime;   //
		//!< @brief  GameLogic�̃v���Z�X�}�l�[�W���[
		ProcessManagerSharedPtr m_pProcessManager;

	public:
		/**
		* @brief ������
		* @param[in] filename �Q�[�����W�b�N��ݒ肷��ׂ̃t�@�C���p�X
		*/
		void Initialize(const char* filename) override;
		/**
		* @brief �X�V
		* @param[in] currentTime ���݂̎���
		* @param[in] elapsedTime ���܂ł̌o�ߎ���
		*/
		void Update(float currentTime, float elapsedTime) override;
		/**
		* @brief �J��
		*/
		void Release() override;
	};
}

