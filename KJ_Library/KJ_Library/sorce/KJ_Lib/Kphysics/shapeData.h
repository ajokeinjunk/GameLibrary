#ifndef __H_SHAPE_DATA_H__
#define __H_SHAPE_DATA_H__
#include "Kmath.h"

#define CONVEX_MESH_MAX_VERTICES 34
#define CONVEX_MESH_MAX_EDGES    96
#define CONVEX_MESH_MAX_FACES    64

namespace Kmath{
	
	
	struct CollidableShape{

	};

	//í∏ì_34ÅAñ 64ÅAï”96à»â∫
	struct ConvexMesh{
		int m_numVertices;
		int m_numFaces;
		int m_numEdges;
		Vector3 m_vertices[CONVEX_MESH_MAX_VERTICES];

	};
}

#endif