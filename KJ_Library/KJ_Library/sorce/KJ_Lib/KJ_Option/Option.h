#pragma once

#include "../KJ_Defines/KJ_Defines.h"

namespace Klibrary{

	struct GameOption
	{
		//�T�E���h�I�v�V����
		//!< @brief BGM�̃{�����[�� 
		jFloat m_BGMVolume;
		//!< @brief SE�̃{�����[��
		jFloat m_SEVolume;

		//�Q�[���I�v�V����
		jUInt32 m_NumAIs;
		jUInt32 m_MaxAIs;

		//�R���g���[���I�v�V����
		bool    m_CameraAxisY;

		GameOption();
	};

}