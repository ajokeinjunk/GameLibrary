#ifndef __H_SHAPE_DATA_H__
#define __H_SHAPE_DATA_H__
#include "Kmath.h"

#define CONVEX_MESH_MAX_VERTICES 34
#define CONVEX_MESH_MAX_EDGES    96
#define CONVEX_MESH_MAX_FACES    64

namespace Kmath{
	
	
	struct CollidableShape{

	};

	//頂点34、面64、辺96以下
	struct ConvexMesh{
		int m_numVertices;
		int m_numFaces;
		int m_numEdges;
		Vector3 m_vertices[CONVEX_MESH_MAX_VERTICES];

	};
}

#endif