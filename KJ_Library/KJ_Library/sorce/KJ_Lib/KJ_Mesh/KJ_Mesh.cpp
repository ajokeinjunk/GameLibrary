#include "KJ_Mesh.h"

namespace Klibrary{

	//========--------========--------========--------========--------========
	//
	//			MeshƒNƒ‰ƒX
	//
	//========--------========--------========--------========--------========
	void KJ_Mesh::Initialize(){

		m_worldTransMatrix.Identify();
		m_pos = Vector3(0,0,0);
		m_rotation = Vector3(0,0,0);
		m_scale = Vector3(1.0f,1.0f,1.0f);
		m_meshInfo = new  MeshVertexInfo();
	}

	void KJ_Mesh::Update(){
		Mat4MakeWorldTransMatrixZXY(m_worldTransMatrix, m_scale, m_rotation, m_pos);
	}
	
	void KJ_Mesh::Render(){
		Renderer->SetWorldTransMatrix(m_worldTransMatrix);
		m_meshInfo->Render();
	}



}//namespace