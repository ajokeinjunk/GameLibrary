#include "OctreeNode.h"

namespace Klibrary{
	void OctreeNode::Initialize(jUInt32 leafType){
		for (jInt16 i = 0; i < 8; i++)
		{
			m_children[i] = leafType | KJ_NODE_LEAF;
		}
	}


}