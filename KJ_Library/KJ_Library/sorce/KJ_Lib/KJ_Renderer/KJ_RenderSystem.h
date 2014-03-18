#ifndef H_KLIB_RENDER_SYSTEM_H
#define H_KLIB_RENDER_SYSTEM_H
#include "KJ_DirectX\KJ_DirectX3D.h"
#include <memory>

namespace Klibrary{

	/** ===================================================================================
	* @class RenderSystem
	* @brief �`��V�X�e���ɃA�N�Z�X����N���X�B
	* ����KdirectX3D�������_���[�ɂȂ��Ă��邪
	* �{�����̊���Krenderer�������_���[�ɂȂ�B
	==================================================================================== */

	typedef std::shared_ptr<KdirectX3D> RendererSharedPtr;

	class RenderSystem{
	private:
		//!< @brief�@�����_���[�B�A�v����1�������݂��Ȃ��B
		static RendererSharedPtr m_renderer;

	public:
		/**
		* @brief ������
		* @return false = ���s�B
		*/
		static bool Initialize();
		/**
		* @brief �j��
		*/
		static void Release();

		//�Q�b�^�[
		static const RendererSharedPtr& GetRenderer(){ return m_renderer; }
	};

#define Renderer (RenderSystem::GetRenderer())
}

#endif