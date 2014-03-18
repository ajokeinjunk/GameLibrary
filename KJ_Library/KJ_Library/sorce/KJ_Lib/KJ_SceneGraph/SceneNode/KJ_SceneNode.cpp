#include "KJ_SceneNode.h"

namespace Klibrary{

	//========--------========--------========--------========--------========
	//
	//			Scene3DNodeクラス
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
	//			CameraNodeクラス
	//
	//========--------========--------========--------========--------========
	void CameraNode::Render(){
#ifdef _DEBUG
		m_Frustum.DebugRender();
#endif
	}
}