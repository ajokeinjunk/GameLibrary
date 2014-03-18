#include "GameView.h"
#include "../KJ_Windows/KJ_WindowSystem.h"
#include "../KJ_Renderer/KJ_RenderSystem.h"
#include <Windows.h>

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			HumanViewƒNƒ‰ƒX
	//
	//========--------========--------========--------========--------========
	HumanView::HumanView(){
		m_ProcessManager = std::make_shared<ProcessManager>();
		m_PointerRadius = 1;
		m_ID = INVALID_GAME_VIEW_ID;

		if (Renderer){
			
		}
	}
	
	HumanView::~HumanView(){

	}

	void HumanView::VUpdate(const jUInt32 deltaMs){
		m_ProcessManager->UpdateProcesses(deltaMs);

		auto end = m_ScreenElementList.end();
		for(auto i = m_ScreenElementList.begin(); i != end; ++i){
			(*i)->VUpdate(deltaMs);
		}
	}

	void HumanView::VRender(){

	}


	void CALLBACK HumanView::VMsgProc(){
		auto end = m_ScreenElementList.end();
		for (auto i = m_ScreenElementList.begin(); i != end; ++i){
			if ((*i)->VIsVisible()){
				(*i)->VMsgProc();
			}
		}

		switch (WindowsMsg::message)
		{
		case WM_KEYDOWN:
			if (m_KeyBoardHandler){
				m_KeyBoardHandler->KeyDown(static_cast<jUInt8>(WindowsMsg::message));
			}
			break;

		case WM_KEYUP:
			if (m_KeyBoardHandler){
				m_KeyBoardHandler->KeyUp(static_cast<jUInt8>(WindowsMsg::message));
			}
			break;

		case WM_MOUSEMOVE:
			if (m_MouseHandler){
				m_MouseHandler->MouseMove(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius);
			}
			break;

		case WM_LBUTTONDOWN:
			if (m_MouseHandler){
				m_MouseHandler->MouseButtonDown(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius, MOUSE_L_BUTTON);
			}
			break;

		case WM_LBUTTONUP:
			if (m_MouseHandler){
				m_MouseHandler->MouseButtonUp(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius, MOUSE_L_BUTTON);
			}
			break;

		case WM_RBUTTONDOWN:
			if (m_MouseHandler){
				m_MouseHandler->MouseButtonDown(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius, MOUSE_R_BUTTON);
			}

		case WM_RBUTTONUP:
			if (m_MouseHandler){
				m_MouseHandler->MouseButtonUp(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius, MOUSE_R_BUTTON);
			}
			break;

		case WM_MBUTTONDOWN:
			if (m_MouseHandler){
				m_MouseHandler->MouseButtonDown(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius, MOUSE_M_BUTTON);
			}
			break;

		case WM_MBUTTONUP:
			if (m_MouseHandler){
				m_MouseHandler->MouseButtonUp(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius, MOUSE_M_BUTTON);
			}
			break;

		default:
			break;
		}
	}

}