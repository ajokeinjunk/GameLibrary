#pragma once

#include "../../KJ_Interface/KJ_Interface.h"
#include "../../KJ_Mesh/MeshProperty.h"
#include <memory>
#include <string>
#include "../../KJ_SceneGraph/SceneNode/KJ_SceneNode.h"
#include "../../KJ_Math/KJ_Math.h"

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			Scene3DNode�N���X
	//
	//========--------========--------========--------========--------========
	class Scene3DNode;
	class Scene3DGraph;


	/** ===================================================================================
	* @class Scene3DNodeProperties
	* @brief 3DSceneGraph�̃m�[�h�̃v���p�e�B�B
	* ���g�̒l��ύX�ł���̂�friend��Scene3DNode�̂݁B
	* ����ȊO�͓ǂݎ���p�ƂȂ�B
	==================================================================================== */
	class Scene3DNodeProperties{
	friend class Scene3DNode;

	protected:
		//!< @brief�@��{�ƂȂ�Actor��ID
		ActorID        m_ModeActorID;
		//!< @brief�@�m�[�h�̖��O�B
		std::string    m_Name;
		//!< @brief�@���[�J�����烏�[���h�ւ̍s��Ƃ��̋t�s��B
		Matrix4        m_ToWarld, m_FromWarld;
		//!< @brief�@�J�����O�p�R���W����
		AABBCenterHalf m_AABB;
		//!< @brief�@�V�F�[�_�[�`��p�̃p�X
		RenderPass     m_RenderPass;    
		//!< @brief�@3D�m�[�h�̃}�e���A���B�m���A
		MaterialSharedPtr     m_Material;      

	public:

		Scene3DNodeProperties(){
			m_ModeActorID = INVALID_ACTOR_ID;
			m_RenderPass = RenderPass_0;
		}

		//�Q�b�^�[
		ActorID                     GetModelActor()const{ return m_ModeActorID; }
		const std::string&          GetName()const{ return m_Name; }
		RenderPass                  GetRenderPass()const{ return m_RenderPass; }
		const MaterialSharedPtr&    GetMaterial()const{ return m_Material; }
		const Matrix4&              GetToWarld()const{ return m_ToWarld; }
		void                        GetTransform(Matrix4& outToWarld, Matrix4& outFromWorld)const{outToWarld = m_ToWarld; outFromWorld = m_FromWarld;}
	
	};

	/** ===================================================================================
	* @class Scene3DNode
	* @brief Scene3DGraph���\������m�[�h�N���X�B
	* �V�[�����\�����邠����3D�v�f���m�[�h�ɂȂ�B
	==================================================================================== */
	class Scene3DNode : public ISceneNode{

		friend class Scene3DGraph;

	protected:
		//!< @brief�@Scene3DNode�̃p�����[�^
		Scene3DNodeProperties m_Properties; 
		//!< @brief�@�e�m�[�h�ւ̃|�C���^�B�����ꍇnullptr�������Ă���B
		Scene3DNode           *m_pParent;    
		//!< @brief�@�q�m�[�h�̃��X�g�B
		SceneNodeList         m_Children;    

	public:
		Scene3DNode(ActorID actorID, RenderPass renderPass, const Matrix4& toWorld){
			m_pParent = nullptr;
			m_Properties.m_ModeActorID = actorID;
			m_Properties.m_Name = "Scene3DNode";
			m_Properties.m_RenderPass = renderPass;
		}

		/**
		* @brief �X�V
		*/
		void VUpdate(const jUInt32 deltaMs) override;
		/**
		* @brief �`��
		*/
		void VRender() override;
		
		/**
		* @brief �ϊ��s���ݒ肷��B���[�J���ւ̕ϊ��s��͓����Őݒ肳���B
		* @param[in] toWorld ���[���h��Ԃւ̕ϊ��s���ݒ肷��B
		*/
		void SetTransform(const Matrix4& toWorld){ m_Properties.m_ToWarld = toWorld; m_Properties.m_ToWarld.Inverse(m_Properties.m_FromWarld); }
		/**
		* @brief �ϊ��s���ݒ肷��
		* @param[in] toWorld ���[���h��Ԃւ̕ϊ��s���ݒ肷��B
		* @param[in] fromWorld ���݂̃m�[�h��Ԃւ̕ϊ��s���ݒ肷��B
		*/
		void SetTransform(const Matrix4& toWorld, const Matrix4& fromWorld){ m_Properties.m_ToWarld = toWorld; m_Properties.m_FromWarld = fromWorld; }

	};

	/** ===================================================================================
	* @class CameraNode
	* @brief �J�����m�[�h�B������J�����B
	==================================================================================== */
	class CameraNode : public Scene3DNode{
	protected:
		//!< @brief ������
		Frustum m_Frustum;
		//!< @brief �ˉe�s��
		Matrix4 m_Projection;
		//!< @brief �r���[�s��
		Matrix4 m_View;
		//!< @brief �J�������ғ���Ԃ��B
		bool    m_IsActivate;


	public:
		CameraNode(const Matrix4 toWorld, const Frustum& frustum)
		: Scene3DNode(INVALID_ACTOR_ID, RenderPass_0, toWorld), m_Frustum(frustum),
		m_IsActivate(true)
		{}

		/**
		* @brief �`��
		*/
		void VRender() override;
	};
}