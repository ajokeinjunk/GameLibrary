#ifndef H_KLIB_UI_H
#define H_KLIB_UI_H

#include "../KJ_Defines/KJ_Defines.h"
#include "../KJ_SceneGraph/SceneGraph.h"
#include "../KJ_Renderer/KJ_RenderSystem.h"
#include <memory>

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
		//			�A�N�Z�T
		//========--------========--------========--------========--------========
		jInt32 GetPosX()const{ return m_posX; }
		jInt32 GetPosY()const{ return m_posY; }
		jUInt32 GetWidth()const{ return m_width; }
		jUInt32 GetHeight()const{ return m_height; }

		//�Z�b�^�[
		void SetPos(jInt32 posX, jInt32 posY){ m_posX = posX; m_posY = posY; }
		void SetPosX(jInt32 posX){ m_posX = posX; }
		void SetPosY(jInt32 posY){ m_posY = posY; }
		void SetWidth(jInt32 width){ m_width = width; }
		void SetHeight(jInt32 height){ m_height = height; }
	};

	/** ===================================================================================
	* @class SceneScreenElement
	* @brief Scene3DGraphic�ŕ`�悳�ꂽ���̂�ScreenElement�Ƃ��Ĉ����N���X
	* Scene3DNode�̏W���̂ł���Scene3DGraph��
	* ��ʂɕ`�悳���1�v�f�Ƃ��Ĉ������Ƃ��ł���B
	==================================================================================== */
	class Scene3DScreenElement : public IScreenElement, public Scene3DGraph{
	private:
	public:
		Scene3DScreenElement(){}
		~Scene3DScreenElement(){}

		void VUpdate(jUInt32 deltaMs) override{ Update(deltaMs); }
		void VRender() override { Render(); return; }

		void CALLBACK VMsgProc()override{ return; }

		//�Q�b�^�[
		jInt32 VGetZOrder()const override{ return 0; }
		bool VIsVisible()const override{ return true; }

		//�Z�b�^�[
		void VSetZOrder(jUInt32)const{}
		void VSetVisible(bool visible)override{}
	};

}

#endif