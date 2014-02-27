#ifndef H_KLIB_MOUSE_H
#define H_KLIB_MOUSE_H


#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "../KJ_Defines/KJ_Defines.h"

#pragma comment(lib, "dinput8.lib")


namespace Klibrary{



	typedef jUInt32 MouseState;

	class Mouse{
	protected:
		enum MouseButton{
			RIGHT_BUTTON = 0,
			MIDDLE_BUTTON,
			LEFT_BUTTON,
			MOUSE_BUTTON_NUM,
		};

		static bool m_Enable; 
		static bool m_Show;
		static bool m_FreezeOnCenter;
		static bool m_IsOnePush;
		static bool m_IsOnePull;

		//MouseState m_state;
		static POINT m_Pos;
		static POINT m_ClientPos;
		static POINT m_LastPos;
		static POINT m_RelativeDistance;

	public:
		Mouse(){
			m_Enable = true;
			m_FreezeOnCenter = false;
			m_Show = true;
			//m_state = 0;
			m_Pos.x = 0;
			m_Pos.y = 0;
			m_LastPos.x = 0; m_LastPos.y;
			m_RelativeDistance.x = 0; m_RelativeDistance.y;
		}


		static void Initialize(){
			m_Enable = true;
			m_FreezeOnCenter = false;
			m_Show = true;
			//m_state = 0;
			m_Pos.x = 0;
			m_Pos.y = 0;
			m_LastPos.x = 0; m_LastPos.y;
			m_RelativeDistance.x = 0; m_RelativeDistance.y;
		}

		//
		static void UpdateTrackMouse();
		

		//アクセサ
		static const POINT& GetPoint(){ return m_Pos; }
		static const POINT& GetClientPoint(){ return m_ClientPos; }
		static const POINT& GetRelativeDistance(){ return m_RelativeDistance; }

		static bool GetFlagEnable(){ return m_Enable; }
		static bool GetFlagFreezeOnCenter(){ return m_FreezeOnCenter; }
		static bool GetFlagShow(){ return m_Show; }
		static bool IsOnePush(){ return m_IsOnePush; }
		static bool IsOnePull(){ return m_IsOnePull; }
		
		static void SetPoint(const POINT& pos){ m_Pos = pos; }
		static void SetPoint(LONG x, LONG y){ m_Pos.x = x; m_Pos.y = y; }
		static void SetEnable(bool flag){ m_Enable = flag; }
		static void SetFreezeOnCenter(bool flag){ m_FreezeOnCenter = flag; }
		static void SetShow(bool flag){ m_Show = flag; }
	};
}

#endif