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
			node->SetIndex((int)(m_nodes.size()));   //Node�͑����邾���Ƃ��Ă���̂�ID����邱�Ƃ͂Ȃ�
			m_nodes.push_back(node);
		}

		bool CreateEdge(Node* head, Node* terminus, bool isTwoWay = true);

		//�Œ�R�X�g�̌o�H�T��
		//�R�X�g�����Ō��߂邩(�ʒu��d�v�x�Ȃ�)��fpCostFunc�Ɋi�[����֐��Ō��߂�B
		float ComputeBestPath(Node* start, Node* goal, float*(fpCostFunc)(Edge *), std::vector<Node>& path);

	protected:
		std::vector<GraphNode*> m_nodes;
		std::vector<GraphEdge*> m_edges;
	
		//�o�H�T���w���p�[���\�b�h
		void InitializePath();
	};


}

#endif