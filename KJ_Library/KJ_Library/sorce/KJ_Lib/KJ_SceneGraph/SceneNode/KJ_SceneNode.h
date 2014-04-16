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
	//			Scene3DNodeクラス
	//
	//========--------========--------========--------========--------========
	class Scene3DNode;
	class Scene3DGraph;


	/** ===================================================================================
	* @class Scene3DNodeProperties
	* @brief 3DSceneGraphのノードのプロパティ。
	* 中身の値を変更できるのはfriendのScene3DNodeのみ。
	* それ以外は読み取り専用となる。
	==================================================================================== */
	class Scene3DNodeProperties{
	friend class Scene3DNode;

	protected:
		//!< @brief　大本となるActorのID
		ActorID        m_ModeActorID;
		//!< @brief　ノードの名前。
		std::string    m_Name;
		//!< @brief　ローカルからワールドへの行列とその逆行列。
		Matrix4        m_ToWarld, m_FromWarld;
		//!< @brief　カリング用コリジョン
		AABBCenterHalf m_AABB;
		//!< @brief　シェーダー描画用のパス
		RenderPass     m_RenderPass;    
		//!< @brief　3Dノードのマテリアル。確か、
		MaterialSharedPtr     m_Material;      

	public:

		Scene3DNodeProperties(){
			m_ModeActorID = INVALID_ACTOR_ID;
			m_RenderPass = RenderPass_0;
		}

		//ゲッター
		ActorID                     GetModelActor()const{ return m_ModeActorID; }
		const std::string&          GetName()const{ return m_Name; }
		RenderPass                  GetRenderPass()const{ return m_RenderPass; }
		const MaterialSharedPtr&    GetMaterial()const{ return m_Material; }
		const Matrix4&              GetToWarld()const{ return m_ToWarld; }
		void                        GetTransform(Matrix4& outToWarld, Matrix4& outFromWorld)const{outToWarld = m_ToWarld; outFromWorld = m_FromWarld;}
	
	};

	/** ===================================================================================
	* @class Scene3DNode
	* @brief Scene3DGraphを構成するノードクラス。
	* シーンを構成するあらゆる3D要素がノードになる。
	==================================================================================== */
	class Scene3DNode : public ISceneNode{

		friend class Scene3DGraph;

	protected:
		//!< @brief　Scene3DNodeのパラメータ
		Scene3DNodeProperties m_Properties; 
		//!< @brief　親ノードへのポインタ。無い場合nullptrが入っている。
		Scene3DNode           *m_pParent;    
		//!< @brief　子ノードのリスト。
		SceneNodeList         m_Children;    

	public:
		Scene3DNode(ActorID actorID, RenderPass renderPass, const Matrix4& toWorld){
			m_pParent = nullptr;
			m_Properties.m_ModeActorID = actorID;
			m_Properties.m_Name = "Scene3DNode";
			m_Properties.m_RenderPass = renderPass;
		}

		/**
		* @brief 更新
		*/
		void VUpdate(const jUInt32 deltaMs) override;
		/**
		* @brief 描画
		*/
		void VRender() override;
		
		/**
		* @brief 変換行列を設定する。ローカルへの変換行列は内部で設定される。
		* @param[in] toWorld ワールド空間への変換行列を設定する。
		*/
		void SetTransform(const Matrix4& toWorld){ m_Properties.m_ToWarld = toWorld; m_Properties.m_ToWarld.Inverse(m_Properties.m_FromWarld); }
		/**
		* @brief 変換行列を設定する
		* @param[in] toWorld ワールド空間への変換行列を設定する。
		* @param[in] fromWorld 現在のノード空間への変換行列を設定する。
		*/
		void SetTransform(const Matrix4& toWorld, const Matrix4& fromWorld){ m_Properties.m_ToWarld = toWorld; m_Properties.m_FromWarld = fromWorld; }

	};

	/** ===================================================================================
	* @class CameraNode
	* @brief カメラノード。いわゆるカメラ。
	==================================================================================== */
	class CameraNode : public Scene3DNode{
	protected:
		//!< @brief 視錘台
		Frustum m_Frustum;
		//!< @brief 射影行列
		Matrix4 m_Projection;
		//!< @brief ビュー行列
		Matrix4 m_View;
		//!< @brief カメラが稼動状態か。
		bool    m_IsActivate;


	public:
		CameraNode(const Matrix4 toWorld, const Frustum& frustum)
		: Scene3DNode(INVALID_ACTOR_ID, RenderPass_0, toWorld), m_Frustum(frustum),
		m_IsActivate(true)
		{}

		/**
		* @brief 描画
		*/
		void VRender() override;
	};
}