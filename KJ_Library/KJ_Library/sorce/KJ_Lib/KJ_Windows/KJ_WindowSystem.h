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


/** ===================================================================================
* @class WindowSystem
* @brief WindowハンドルやWindow情報へのアクセサー
==================================================================================== */
namespace Klibrary{
	class WindowSystem{
	private:

	public:
		//!< @brief ウィンドウの高さ
		static WORD windowHeight;
		//!< @brief ウィンドウの幅
		static WORD windowWidth;
		//!< @brief ウィンドウハンドル
		static HWND hWnd; 

		//ゲッター
		inline static float GetScreenAspectRatio(){return (float)windowWidth/windowHeight;}
	};

	/** ===================================================================================
	* @class WindowsMsg
	* @brief Windowから送られてくるメッセージの構造体
	* 直前の入力メッセージも保管している。
	==================================================================================== */
	class WindowsMsg{
	public:
		static UINT message;
		static WPARAM wParam;
		static LPARAM lParam;
		static UINT lastMessage;
	};

}//namespace

#endif