#pragma once

#include "../KJ_Defines/KJ_Defines.h"

namespace Klibrary{

	struct GameOption
	{
		//サウンドオプション
		//!< @brief BGMのボリューム 
		jFloat m_BGMVolume;
		//!< @brief SEのボリューム
		jFloat m_SEVolume;

		//ゲームオプション
		jUInt32 m_NumAIs;
		jUInt32 m_MaxAIs;

		//コントロールオプション
		bool    m_CameraAxisY;

		GameOption();
	};

}