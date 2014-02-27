#ifndef H_KLIB_WINDOW_SYSTEM_H
#define H_KLIB_WINDOW_SYSTEM_H

#pragma warning(disable:4005)

#include "../KJ_Renderer/KJ_DirectX/KJ_DirectX3D.h"
#include "../KJ_Renderer/KJ_Renderer.h"
#include <Windows.h>


//マクロ


//定義	


//定数定義
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

//========--------========--------========--------========--------========
//
//			KwindowSystemクラス
//
//========--------========--------========--------========--------========

namespace Klibrary{
	class WindowSystem{
	private:

	public:
		static WORD windowHeight;
		static WORD windowWidth;
		static HWND hWnd;  //ウィンドウハンドル

		inline static float GetScreenAspectRatio(){return (float)windowWidth/windowHeight;}
	};
}//namespace

#endif