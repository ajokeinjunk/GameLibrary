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


/** ===================================================================================
* @class WindowSystem
* @brief Window�n���h����Window���ւ̃A�N�Z�T�[
==================================================================================== */
namespace Klibrary{
	class WindowSystem{
	private:

	public:
		//!< @brief �E�B���h�E�̍���
		static WORD windowHeight;
		//!< @brief �E�B���h�E�̕�
		static WORD windowWidth;
		//!< @brief �E�B���h�E�n���h��
		static HWND hWnd; 

		//�Q�b�^�[
		inline static float GetScreenAspectRatio(){return (float)windowWidth/windowHeight;}
	};

	/** ===================================================================================
	* @class WindowsMsg
	* @brief Window���瑗���Ă��郁�b�Z�[�W�̍\����
	* ���O�̓��̓��b�Z�[�W���ۊǂ��Ă���B
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