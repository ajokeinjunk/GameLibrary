#ifndef H_KLIB_UI_H
#define H_KLIB_UI_H

#include "../KJ_Defines/KJ_Defines.h"

namespace Klibrary{
	class BaseUI
	{
	protected:
		jInt32 m_posX, m_posY;
		jInt32 m_width, m_height;
		jBool  m_isVisible;

	public:
		BaseUI(): m_isVisible(true), m_posX(0), m_posY(0), m_width(100), m_height(100){}
		virtual ~BaseUI();

		//========--------========--------========--------========--------========
		//			アクセサ
		//========--------========--------========--------========--------========
		jInt32 GetPosX()const{ return m_posX; }
		jInt32 GetPosY()const{ return m_posY; }
		jUInt32 GetWidth()const{ return m_width; }
		jUInt32 GetHeight()const{ return m_height; }

		void SetPos(jInt32 posX, jInt32 posY){ m_posX = posX; m_posY = posY; }
		void SetPosX(jInt32 posX){ m_posX = posX; }
		void SetPosY(jInt32 posY){ m_posY = posY; }
		void SetWidth(jInt32 width){ m_width = width; }
		void SetHeight(jInt32 height){ m_height = height; }
	};


}

#endif