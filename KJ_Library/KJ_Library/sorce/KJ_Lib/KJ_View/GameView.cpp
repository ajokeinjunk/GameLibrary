#include "GameView.h"
#include "../KJ_Windows/KJ_WindowSystem.h"
#include "../KJ_Renderer/KJ_RenderSystem.h"
#include <Windows.h>

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			HumanView�N���X
	//
	//========--------========--------========--------========--------========
	HumanView::HumanView(){
		m_ProcessManager = std::make_shared<ProcessManager>();
		m_PointerRadius = 1;
		m_ID = INVALID_GAME_VIEW_ID;
		m_LastDrawTime = 0;
		m_CurrentTime = 0;

		if (Renderer){
			
		}
	}
	
	HumanView::~HumanView(){

	}

	void HumanView::VInitialize(){
		auto it = m_ScreenElementList.begin();
		auto end = m_ScreenElementList.end();
		for (; it != end; ++it){
			(*it)->VInitialize();
		}
	}

	void HumanView::VUpdate(const jUInt32 deltaMs){
		m_ProcessManager->UpdateProcesses(deltaMs);

		auto end = m_ScreenElementList.end();
		for(auto i = m_ScreenElementList.begin(); i != end; ++i){
			(*i)->VUpdate(deltaMs);
		}
	}

	void HumanView::VRender(){
		m_CurrentTime = timeGetTime();
		if (m_CurrentTime == m_LastDrawTime){return;}

		if ((m_CurrentTime - m_LastDrawTime) > SCREEN_REFRESH_RATE){
			//if (Renderer->BeginRender())
		}
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
				m_KeyBoardHandler->VKeyDown(static_cast<jUInt8>(WindowsMsg::message));
			}
			break;

		case WM_KEYUP:
			if (m_KeyBoardHandler){
				m_KeyBoardHandler->VKeyUp(static_cast<jUInt8>(WindowsMsg::message));
			}
			break;

		case WM_MOUSEMOVE:
			if (m_MouseHandler){
				m_MouseHandler->VMouseMove(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius);
			}
			break;

		case WM_LBUTTONDOWN:
			if (m_MouseHandler){
				m_MouseHandler->VMouseButtonDown(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius, MOUSE_L_BUTTON);
			}
			break;

		case WM_LBUTTONUP:
			if (m_MouseHandler){
				m_MouseHandler->VMouseButtonUp(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius, MOUSE_L_BUTTON);
			}
			break;

		case WM_RBUTTONDOWN:
			if (m_MouseHandler){
				m_MouseHandler->VMouseButtonDown(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius, MOUSE_R_BUTTON);
			}

		case WM_RBUTTONUP:
			if (m_MouseHandler){
				m_MouseHandler->VMouseButtonUp(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius, MOUSE_R_BUTTON);
			}
			break;

		case WM_MBUTTONDOWN:
			if (m_MouseHandler){
				m_MouseHandler->VMouseButtonDown(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius, MOUSE_M_BUTTON);
			}
			break;

		case WM_MBUTTONUP:
			if (m_MouseHandler){
				m_MouseHandler->VMouseButtonUp(Point2L(LOWORD(WindowsMsg::lParam), HIWORD(WindowsMsg::lParam)), m_PointerRadius, MOUSE_M_BUTTON);
			}
			break;

		default:
			break;
		}
	}



}