#include "Mouse.h"

namespace Klibrary{
	bool Mouse::m_Enable = true;
	bool Mouse::m_Show = true;
	bool Mouse::m_FreezeOnCenter = false;
	
	//POINT Mouse::m_pos;
	//POINT Mouse::m_lastPos;
	//POINT Mouse::m_relativeDistance;


	void Mouse::UpdateTrackMouse(){


		if (!m_Enable)return;

		//GetCursorPos(&m_pos);  //����̓X�N���[���̍��W�Ȃ̂�
		m_relativeDistance.x = m_lastPos.x - m_pos.x;
		m_relativeDistance.y = m_lastPos.y - m_pos.y;

		if (m_FreezeOnCenter){
			//m_pos.x = iexSystem::ScreenWidth / 2;
			//m_pos.y = iexSystem::ScreenHeight / 2;
			//ClientToScreen(iexSystem::Window, &m_pos);//���݉�ʊ�̍��W��m_pos��ϊ�

			//SetCursorPos(m_pos.x, m_pos.y);
		}
	
			//�����ŎZ�o����Ă���̂͂����܂ŉ�ʏ�̃J�[�\���ړ���



		m_lastPos = m_pos;


	}

	/*void Mouse::SetupMouseState(){
		switch (g_wparam)
		{
		case WM_LBUTTONDOWN:
			m_mouseButtonState[LEFT_BUTTON] |= MOUSE_PUSH;

		case WM_MBUTTONDOWN:
			m_mouseButtonState[MIDDLE_BUTTON] |= MOUSE_PUSH;

		case WM_RBUTTONDOWN:
			m_mouseButtonState[RIGHT_BUTTON] |= MOUSE_PUSH;

		case WM_LBUTTONUP:
			m_mouseButtonState[LEFT_BUTTON] |= MOUSE_UP;

		case WM_MBUTTONUP:
			m_mouseButtonState[MIDDLE_BUTTON] |= MOUSE_UP;

		case WM_RBUTTONUP:
			m_mouseButtonState[RIGHT_BUTTON] |= MOUSE_UP;

			case WM
		default:
			break;
		}
	}*/


}