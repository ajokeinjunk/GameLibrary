#include "KJ_SceneNode.h"

namespace Klibrary{

	//========--------========--------========--------========--------========
	//
	//			Scene3DNode�N���X
	//
	//========--------========--------========--------========--------========
	void Scene3DNode::Update(const jUInt32 deltaMs){
		auto i = m_Children.begin();
		auto end = m_Children.end();

		while (i != end){
			(*i)->Update(deltaMs);
			++i;
		}
	}

	void Scene3DNode::Render(){
	}

	//========--------========--------========--------========--------========
	//
	//			CameraNode�N���X
	//
	//========--------========--------========--------========--------========
	void CameraNode::Render(){
#ifdef _DEBUG
		m_Frustum.DebugRender();
#endif
	}
}