#include "InputDeviceManager.h"

using namespace std;

namespace Klibrary{
	shared_ptr<Mouse> InputDeviceManager::m_mouse = make_shared<Mouse>();
	jUInt8            InputDeviceManager::m_ActivateDevice = 0;

	void InputDeviceManager::Initialize(){
		m_ActivateDevice |= ALL_ENABLE;

	}

	void InputDeviceManager::Update(jUInt32 deltaMs){
		if (!(m_ActivateDevice & ALL_ENABLE)){ return; }


		if (m_ActivateDevice & MOUSE_ENABLE){
			m_mouse->UpdateTrackMouse();
		}
		if (m_ActivateDevice & KEYBOARD_ENABLE){
		}
		if (m_ActivateDevice & JOYSTICK_ENABLE){
		}
	}


}