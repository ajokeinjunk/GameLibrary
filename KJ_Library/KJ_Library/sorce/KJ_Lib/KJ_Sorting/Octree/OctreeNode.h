#ifndef H_KLIB_OCTREE_NODE_H
#define H_KLIB_OCTREE_NODE_H

#include "OctreeData.h"
#include "../../KJ_Math/KJ_Math.h"

namespace Klibrary{
	class Octree;

	class OctreeNode
	{
	public:
		OctreeNode();
		~OctreeNode();

		void Initialize(jUInt32 leafType);

		void Traverse(void*          userData,   
					  Octree*        tree,
			          jUInt32        size,
					  const Vector3& minPoint, 
				     jUInt32         leafData);

	protected:
		NodeIndexData m_children[8];

	};
	OctreeNode::OctreeNode()
	{

	}

	OctreeNode::~OctreeNode()
	{

	}
}

#endif