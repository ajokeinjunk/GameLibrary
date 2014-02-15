#include "Octree.h"

namespace Klibrary{

	Octree::Octree(jUInt32 depth, jUInt32 leafType){
		m_freeIndex = KJ_NODE_INVALID;
		m_nextIndex = KJ_NODE_NONE;

		m_depthLevel = depth;

		//ルートノード作成、設定


	}

	NodeIndexData Octree::CreateNode(){
		//空ならノードの中身作成
		if (m_freeIndex == KJ_NODE_INVALID){

		}
		return 0;
	}

}
