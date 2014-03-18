#include "Mouse.h"
#include "../KJ_Windows/KJ_WindowSystem.h"

namespace Klibrary{
	bool Mouse::m_Enable = true;
	bool Mouse::m_Show = true;
	bool Mouse::m_FreezeOnCenter = false;
	bool Mouse::m_IsOnePush = false;
	bool Mouse::m_IsOnePull = false;
	
	POINT Mouse::m_Pos;
	POINT Mouse::m_LastPos;
	POINT Mouse::m_RelativeDistance;
	POINT Mouse::m_ClientPos;

	void Mouse::UpdateTrackMouse(){
		if (!m_Enable)return;
		
#ifdef _DEBUG
		//if (KEY_Get(KEY_D) == 3){
		//	m_FreezeOnCenter = !m_FreezeOnCenter;
		//}
#endif
		ShowCursor(m_Show);

		m_IsOnePush = false;
		m_IsOnePull = false;

		if (WindowsMsg::message == WM_LBUTTONDOWN){
			if (WindowsMsg::message != WindowsMsg::lastMessage){
				m_IsOnePush = true;
			}
		}
		else if (WindowsMsg::message == WM_LBUTTONUP){
			if (WindowsMsg::message != WindowsMsg::lastMessage){
				m_IsOnePull = true;
			}
		}

		GetCursorPos(&m_Pos);  //����̓p�\�R����ʂ̍��W
		m_RelativeDistance.x = m_LastPos.x - m_Pos.x;
		m_RelativeDistance.y = m_LastPos.y - m_Pos.y;

		if (m_FreezeOnCenter){
			m_Pos.x = WindowSystem::windowWidth / 2;
			m_Pos.y = WindowSystem::windowHeight / 2;
			ClientToScreen(WindowSystem::hWnd, &m_Pos);//window�̐^�񒆂̓_�����݂̉�ʊ�̍��W��m_pos��ϊ�
			SetCursorPos(m_Pos.x, m_Pos.y);
		}
	
			//�����ŎZ�o����Ă���̂͂����܂ŉ�ʏ�̃J�[�\���ړ���
		m_ClientPos = m_Pos;
		ScreenToClient(WindowSystem::hWnd, &m_ClientPos);

		m_LastPos = m_Pos;
	}



}