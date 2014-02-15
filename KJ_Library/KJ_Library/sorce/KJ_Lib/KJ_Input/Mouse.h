#ifndef H_KLIB_MOUSE_H
#define H_KLIB_MOUSE_H

//#include <dinput.h>
#include "../KJ_Defines/KJ_Defines.h"



namespace Klibrary{

	class IPointerHandler
	{
	public:
		//virtual bool VOnMouseMove(const Point &pos, const int radius) = 0;
		//virtual bool VOnPointerButtonDown(const Point &pos, const int radius, const std::string &buttonName) = 0;
		//virtual bool VOnPointerButtonUp(const Point &pos, const int radius, const std::string &buttonName) = 0;
	};

	typedef jUInt32 MouseState;

	class Mouse{
	protected:
		enum MouseButton{
			RIGHT_BUTTON = 0,
			MIDDLE_BUTTON,
			LEFT_BUTTON,
			MOUSE_BUTTON_NUM,
		};

		static bool m_Enable; //lolあとでMouseStateにまとめる。
		static bool m_Show;
		static bool m_FreezeOnCenter;

		//MouseState m_state;
		static POINT m_pos;
		static POINT m_lastPos;
		static POINT m_relativeDistance;


	public:
		Mouse(){

		}


		static void Initialize(){
			m_Enable = true;
			m_FreezeOnCenter = false;
			m_Show = true;
			//m_state = 0;
			m_pos.x = 0;
			m_pos.y = 0;
			m_lastPos.x = 0; m_lastPos.y;
			m_relativeDistance.x = 0; m_relativeDistance.y;
		}

		//
		static void UpdateTrackMouse();
		

		//アクセサ
		static const POINT& GetPoint(){ return m_pos; }
		static const POINT& GetRelativeDistance(){ return m_relativeDistance; }

		static bool GetFlagEnable(){ return m_Enable; }
		static bool GetFlagFreezeOnCenter(){ return m_FreezeOnCenter; }
		static bool GetFlagShow(){ return m_Show; }
		
		static void SetPoint(const POINT& pos){ m_pos = pos; }
		static void SetPoint(LONG x, LONG y){ m_pos.x = x; m_pos.y = y; }
		static void SetEnable(bool flag){ m_Enable = flag; }
		static void SetFreezeOnCenter(bool flag){ m_FreezeOnCenter = flag; }
		static void SetShow(bool flag){ m_Show = flag; }
	};
}

#endif