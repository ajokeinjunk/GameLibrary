#include "Octree.h"

namespace Klibrary{

	Octree::Octree(jUInt32 depth, jUInt32 leafType){
		m_freeIndex = KJ_NODE_INVALID;
		m_nextIndex = KJ_NODE_NONE;

		m_depthLevel = depth;

		//���[�g�m�[�h�쐬�A�ݒ�


	}

	NodeIndexData Octree::CreateNode(){
		//��Ȃ�m�[�h�̒��g�쐬
		if (m_freeIndex == KJ_NODE_INVALID){

		}
		return 0;
	}

}
