#ifndef H_KLIB_INPUT_DEVICE_MANAGER_H
#define H_KLIB_INPUT_DEVICE_MANAGER_H

#include "../KJ_Defines/KJ_Defines.h"

namespace Klibrary{
	class IMouseHandler{
		virtual bool ButtonDown() = 0;
		virtual bool ButtonUpd() = 0;
		virtual bool ButtonMove() = 0;
		virtual bool MiddleButtonDrag() = 0;
	};

	class IKeyboardHandler{
	public:
		virtual bool KeyDown(const jUInt8 c) = 0;
		virtual bool KeyUp(const jUInt8 c) = 0;
	};

}

#endif