#ifndef H_KLIB_BASE_GAME_LIGIC_3D_H
#define H_KLIB_BASE_GAME_LIGIC_3D_H

#include "../../KJ_Interface/KJ_Interface.h"
#include "../../KJ_Process/ProcessManager.h"

namespace Klibrary{

	class BaseGameLogic : public IGameLogic{
	protected:
		float m_LifeTime;   //���̃Q�[�������s����Ă���o�߂�������
		ProcessManagerSharedPtr m_pProcessManager;

	public:
		void Initialize(const char* filename) override;
		void Update(float currentTime, float elapsedTime) override;

		void Release() override;


	};
}

#endif