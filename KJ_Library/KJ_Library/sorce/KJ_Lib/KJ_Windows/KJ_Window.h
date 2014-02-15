#ifndef H_KLIB_WINDOW_H
#define H_KLIB_WINDOW_H

#pragma warning(disable:4005)

#include "../KJ_Framework\KJ_Framework.h"
#include "../KJ_Windows\KJ_WindowSystem.h"

#include <windows.h>
#pragma comment(lib, "winmm.lib")

//Windows
HRESULT InitializeWindow(HINSTANCE, INT windowWidth, INT windowHeight, LPCSTR windowName); //ウィンドウ初期化,更新
LRESULT MsgProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

namespace Klibrary{

}

#endif