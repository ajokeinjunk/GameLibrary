#ifndef H_KLIB_MESH_H
#define H_KLIB_MESH_H

#include "../KJ_Math/KJ_Math.h"
#include "../KJ_Windows/KJ_WindowSystem.h"
#include "../KJ_Mesh/MeshProperty.h"
#include "../KJ_Renderer/KJ_RenderSystem.h"
#include "../KJ_SceneGraph/SceneNode/KJ_SceneNode.h"

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			MeshNode(仮)クラス
	//
	//========--------========--------========--------========--------========
	class MeshNode : public Scene3DNode{
	protected:
		char* m_MeshFileName; 

	public:
		MeshNode(ActorID actorID, char* meshFileName, RenderPass renderPass, const Matrix4& toWorld) :Scene3DNode(actorID, renderPass, toWorld){
			m_MeshFileName = meshFileName;
		}
		virtual void VRender() override;
	};

	//========--------========--------========--------========--------========
	//
	//			Meshクラス
	//
	//========--------========--------========--------========--------========
	class KJ_Mesh{
	protected:

		MeshVertexInfo* m_meshInfo;

		Matrix4 m_worldTransMatrix;
		
		Vector3 m_pos;
		Vector3 m_rotation;
		Vector3 m_scale;


	public:
		inline KJ_Mesh();
		inline virtual ~KJ_Mesh();

		virtual void Initialize();
		virtual void Update();

		void Render();
		void Release(){ SAFE_DELETE(m_meshInfo); }

		//========--------========--------========--------========--------========
		//			アクセサ
		//========--------========--------========--------========--------========
		inline void SetPosition(const Vector3& pos){m_pos = pos;}
		inline void SetPosition(jFloat x, jFloat y, jFloat z){ m_pos.x = x; m_pos.y = y; m_pos.z = z; }
		inline void SetRotation(const Vector3& rotation){m_rotation = rotation;}
		inline void SetRotation(jFloat x, jFloat y, jFloat z){ m_rotation.x = x; m_rotation.y = y; m_rotation.z = z; }
		inline void SetAngle(jFloat angle){ m_rotation.y = angle; }
		inline void SetScale(const Vector3& scale){m_scale = scale;}
		inline void SetScale(jFloat x, jFloat y, jFloat z){ m_scale.x = x; m_scale.y = y; m_scale.z = z; }
		inline void SetScale(jFloat scale){ m_scale.x = scale; m_scale.y = scale; m_scale.z = scale; }


		inline const Vector3& GetPosition()const{return m_pos;}
		inline const Vector3& GetRotation()const{return m_rotation;}
		inline const Vector3& GetScale()const{return m_scale;}
		inline const Matrix4& GetWorldTransMatrix()const{return m_worldTransMatrix;}

	};

	inline KJ_Mesh::KJ_Mesh(){
			m_worldTransMatrix.Identify();

			m_pos.x = 0;
			m_pos.y = 0;
			m_pos.z = 0;

			m_rotation.x = 0;
			m_rotation.y = 0;
			m_rotation.z = 0;

			m_meshInfo = nullptr;
	};

	inline KJ_Mesh::~KJ_Mesh(){
		SAFE_DELETE(m_meshInfo);
	};

	//========--------========--------========--------========--------========
	//
	//			NonAnimationMeshクラス
	//
	//========--------========--------========--------========--------========


}//namespace

#endif