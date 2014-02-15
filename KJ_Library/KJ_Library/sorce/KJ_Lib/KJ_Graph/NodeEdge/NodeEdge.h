#ifndef H_KLIB_NODE_EDGE_H
#define H_KLIB_NODE_EDGE_H

#include <vector>

namespace Klibrary{
	class GraphNode;

	class GraphEdge
	{
	public:
		GraphEdge() :m_terminus(nullptr), m_head(nullptr){}
		virtual ~GraphEdge(){};

		const GraphNode* GetTerminus()const{ return m_terminus; }
		const GraphNode* GetHead()const{ return m_head; }

		void SetTerminus(GraphNode* terminus){ m_terminus = terminus; }
		void SetHead(GraphNode* head){ m_head = head; }

	protected:
		GraphNode* m_terminus;
		GraphNode* m_head;
	};

	class GraphNode
	{
	public:
		GraphNode() :m_index(-1), m_searchCost(FLT_MAX), m_lead(nullptr){ m_edges.reserve(5); }
		GraphNode(unsigned int edgeNum) :m_index(-1), m_searchCost(FLT_MAX), m_lead(nullptr){ m_edges.reserve(edgeNum); }

		virtual ~GraphNode(){}

		void AddEdge(GraphEdge* edge);

		const std::vector<GraphEdge*>& GetEdges(){ return m_edges; }
		int GetIndex()const{ return m_index; }
		float GetSearchCost()const{ return m_searchCost; }
		GraphNode* GetLead()const{ return m_lead; } //先頭ノードを取得する

		void SetIndex(int index){ m_index = index; }
		void SetSearchCost(float searchCost){ m_searchCost = searchCost; }
		void SetLead(GraphNode* lead){ m_lead = lead; }

	protected:
		std::vector<GraphEdge*> m_edges;
		int m_index;

		float m_searchCost;  //何故ここにあるか
		GraphNode* m_lead; //最低コストで行けるノード？

	};
}

#endif