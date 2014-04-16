#include "KJ_SceneNode.h"

namespace Klibrary{

	//========--------========--------========--------========--------========
	//
	//			Scene3DNode�N���X
	//
	//========--------========--------========--------========--------========
	void Scene3DNode::VUpdate(const jUInt32 deltaMs){
		auto i = m_Children.begin();
		auto end = m_Children.end();

		while (i != end){
			(*i)->VUpdate(deltaMs);
			++i;
		}
	}

	void Scene3DNode::VRender(){
	}

	//========--------========--------========--------========--------========
	//
	//			CameraNode�N���X
	//
	//========--------========--------========--------========--------========
	void CameraNode::VRender(){
#ifdef _DEBUG
		m_Frustum.DebugRender();
#endif
	}
}