#include "KJ_WindowSystem.h"

namespace Klibrary{

	WORD WindowSystem::windowHeight = WINDOW_HEIGHT;
	WORD WindowSystem::windowWidth = WINDOW_WIDTH;
	HWND WindowSystem::hWnd = nullptr;

	UINT WindowsMsg::message = 0;
	WPARAM WindowsMsg::wParam = NULL;
	LPARAM WindowsMsg::lParam = NULL;
	UINT   WindowsMsg::lastMessage = 0;

	//Krenderer* KwindowSystem::m_renderer = nullptr;
}//namespace