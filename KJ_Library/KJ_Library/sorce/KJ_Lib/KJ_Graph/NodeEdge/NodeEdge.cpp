#include "NodeEdge.h"

namespace Klibrary{
	void GraphNode::AddEdge(GraphEdge* edge){
		m_edges.push_back(edge);
	}
}