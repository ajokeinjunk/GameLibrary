#pragma once 

#include "SceneNode\KJ_SceneNode.h"
#include "../KJ_Renderer/KJ_Renderer.h"
#include <memory>

namespace Klibrary{
	/** ===================================================================================
	* @class Scene3DGraph
	* @brief 3DSceneNode���Ǘ���Scene���\������N���X�B
	* 3DSceneNode�̍X�V�A�`��A�ǉ��A�폜���̊Ǘ����s���ŏ�ʂ̃G���g���[�|�C���g�B
	* �A�N�^�[�̉���Ԃ̃R���|�[�l���g���ǂ�3DSceneNode�����Ǘ����Ă���B
	==================================================================================== */
	class Scene3DGraph{
	protected:
		//!< @brief�@����Ԃ�Scene3DNode�݂̂ō\�������V�[���̃��[�g�m�[�h�B
		std::shared_ptr<Scene3DNode> m_RootNode;
		//!< @brief  Scene���̃J�����BManager�������Ă��Ă����������B
		std::shared_ptr<CameraNode>  m_Camera;

	public:
		Scene3DGraph();
		virtual ~Scene3DGraph(){}

		/**
		* @brief �X�V
		*/
		void Update(jUInt32 deltaMs);
		/**
		* @brief �`��
		*/
		void Render();
	};
}