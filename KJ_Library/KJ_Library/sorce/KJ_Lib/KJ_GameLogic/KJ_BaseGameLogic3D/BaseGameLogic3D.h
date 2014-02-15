#ifndef H_KLIB_BASE_GAME_LIGIC_3D_H
#define H_KLIB_BASE_GAME_LIGIC_3D_H

#include "../../KJ_Interface/KJ_Interface.h"

namespace Klibrary{

	class BaseGameLogic3D : public IGameLogic{
	public:
		void Initialize(const char* filename) override;
		void Update();

		void Release();

	};
}

#endif