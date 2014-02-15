#ifndef H_KLIB_INPUT_DATA_H
#define H_KLIB_INPUT_DATA_H

#include <Windows.h>

namespace Klibrary{
	class WindowsMsg{
	public:
		static HWND hWnd;
		static UINT message;
		static WPARAM wParam;
		static LPARAM lParam;
		static UINT lastMassage;
	};
}

#endif