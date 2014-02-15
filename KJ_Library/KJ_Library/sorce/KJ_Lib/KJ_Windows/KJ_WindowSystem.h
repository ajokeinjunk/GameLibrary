#ifndef H_KLIB_WINDOW_SYSTEM_H
#define H_KLIB_WINDOW_SYSTEM_H

#pragma warning(disable:4005)

#include "../KJ_Renderer/KJ_DirectX/KJ_DirectX3D.h"
#include "../KJ_Renderer/KJ_Renderer.h"
#include <Windows.h>


//�}�N��


//��`	


//�萔��`
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

//========--------========--------========--------========--------========
//
//			KwindowSystem�N���X
//
//========--------========--------========--------========--------========

namespace Klibrary{
	class KwindowSystem{
	private:
		static WORD m_windowHeight;
		static WORD m_windowWidth;

	public:
		static HWND m_hWnd;  //�E�B���h�E�n���h��
		//static Krenderer* m_renderer;

		inline static WORD GetWindowHeight(){return m_windowHeight;}
		inline static WORD GetWindowWidth(){return m_windowWidth;}
		inline static float GetScreenAspectRatio(){return (float)m_windowWidth/m_windowHeight;}
	};
}//namespace

#endif