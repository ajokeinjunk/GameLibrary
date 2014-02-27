#ifndef H_KLIB_INPUT_DEVICE_MANAGER_H
#define H_KLIB_INPUT_DEVICE_MANAGER_H

#include "Mouse.h"
#include <memory>
#include "../KJ_Defines/KJ_Defines.h"

namespace Klibrary{
	//キーボード、パッド、マウス管理
	//キー割り当て、互換できるならなおよし。
	//例えば、Qキーとマウス左がすぐ変えれるとか。

#define MOUSE_ENABLE   0x01
#define KEYBOARD_ENABLE 0x02
#define JOYSTICK_ENABLE 0x04
#define ALL_ENABLE      0x80

	class InputDeviceManager{
	private:
		static std::shared_ptr<Mouse> m_mouse;
		static jUInt8 m_ActivateDevice;

	public:
		InputDeviceManager(){}
		static void Initialize();
		static void Update(jUInt32 deltaMs);

		static void EnableMouse(){ m_ActivateDevice |= MOUSE_ENABLE; }
		static void EnableKeyBoard(){ m_ActivateDevice |= KEYBOARD_ENABLE; }
		static void EnableJoyStick(){ m_ActivateDevice |= JOYSTICK_ENABLE; }
		static void DisableMouse(){ m_ActivateDevice ^= MOUSE_ENABLE; }
		static void DisableKeyBoard(){ m_ActivateDevice ^= KEYBOARD_ENABLE; }
		static void DisableJoyStick(){ m_ActivateDevice ^= JOYSTICK_ENABLE; }

		static inline const std::shared_ptr<Mouse> GetMouse(){ return m_mouse; }
	};
}

#endif