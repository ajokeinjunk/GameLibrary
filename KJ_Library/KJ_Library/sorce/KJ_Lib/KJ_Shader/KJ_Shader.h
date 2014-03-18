#pragma once

#include "../KJ_Renderer/KJ_DirectX/KJ_DirectX3D.h"
#include "../KJ_System/KJ_System.h"

namespace Klibrary{
	class Scene3DNode;
	class Scene3DGraph;

	/** ===================================================================================
	* @class DX11_VertexShader
	* @brief DirectX11��p���_�V�F�[�_�[�N���X
	* Layout��Shader,�R���X�^���g�o�b�t�@�[����͗p�o�b�t�@�[�������B
	==================================================================================== */
	class DX11_VertexShader{
	protected:
		//!< @brief ���_�V�F�[�_�[���̓��C�A�E�g
		ID3D11InputLayout*  m_pVertexLayout;
		//!< @brief ���_�V�F�[�_�[�f�[�^
		ID3D11VertexShader* m_pVertexShader;
		//!< @brief �s��p�R���X�^���g�o�b�t�@�[
		ID3D11Buffer*       m_pMatrices;

	public:
		DX11_VertexShader() : m_pVertexLayout(nullptr), m_pVertexShader(nullptr), m_pMatrices(nullptr){}
		~DX11_VertexShader(){
			SAFE_RELEASE(m_pVertexLayout);
			SAFE_RELEASE(m_pVertexShader);
			SAFE_RELEASE(m_pMatrices);
		}

		/**
		* @brief value�̐�Βl���v�Z���A���ʂ�Ԃ�
		* @param[in] scene ���[���h�ݒ�̊�ƂȂ�Scene
		* @param[in] node �V�F�[�_�[��K�p������Node
		* @return �Z�b�g�A�b�v�Ɏ��s�����ꍇ�Afalse��Ԃ��B
		*/
		bool SetUpRenderer(const Scene3DGraph scene, const Scene3DNode& node);
	};

	/** ===================================================================================
	* @class DX11_PixelShader
	* @brief DirectX11��p�s�N�Z���V�F�[�_�[�N���X
	* Layout��Shader,�R���X�^���g�o�b�t�@�[����͗p�o�b�t�@�[�������B
	==================================================================================== */
	class DX11_PixelShader{
	protected:
		//!< @brief Texture��(�v�ǋL)
		char*              m_TextureResource;
		//!< @brief �s�N�Z���V�F�[�_�[�f�[�^
		ID3D11PixelShader* m_pPixelShader;

	public:
		DX11_PixelShader() : m_pPixelShader(nullptr){}
		~DX11_PixelShader(){
			SAFE_RELEASE(m_pPixelShader);
		}

		/**
		* @brief value�̐�Βl���v�Z���A���ʂ�Ԃ�
		* @param[in] scene ���[���h�ݒ�̊�ƂȂ�Scene
		* @param[in] node �V�F�[�_�[��K�p������Node
		* @return �Z�b�g�A�b�v�Ɏ��s�����ꍇ�Afalse��Ԃ��B
		*/
		bool SetUpRenderer(const Scene3DGraph scene, const Scene3DNode& node);
	};
}

