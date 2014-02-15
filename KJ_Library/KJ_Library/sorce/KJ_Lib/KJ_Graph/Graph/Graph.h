#ifndef H_KLIB_GRAPH_H
#define H_KLIB_GRAPH_H

#include <vector>
#include "../NodeEdge/NodeEdge.h"

namespace Klibrary{

	class GraphNode;


	template<class Node, class Edge>
	class BaseGraph
	{
	public:

		BaseGraph(){
			m_nodes.reserve(50);
			m_edges.reserve(50);}

		BaseGraph(unsigned int numNodes){
			m_nodes.reserve(numNodes);
			m_edges.reserve(numNodes);}

		virtual ~BaseGraph(){
		}

		void Release();

		Node* GetNode(int index){ return m_nodes[index]; }
		Edge* GetEdge(int index){ return m_edges[index]; }

		void AddNode(Node* node){
			node->SetIndex((int)(m_nodes.size()));   //Nodeは増えるだけとしているのでIDが被ることはない
			m_nodes.push_back(node);
		}

		bool CreateEdge(Node* head, Node* terminus, bool isTwoWay = true);

		//最低コストの経路探索
		//コストを何で決めるか(位置や重要度など)はfpCostFuncに格納する関数で決める。
		float ComputeBestPath(Node* start, Node* goal, float*(fpCostFunc)(Edge *), std::vector<Node>& path);

	protected:
		std::vector<GraphNode*> m_nodes;
		std::vector<GraphEdge*> m_edges;
	
		//経路探索ヘルパーメソッド
		void InitializePath();
	};


}

#endif