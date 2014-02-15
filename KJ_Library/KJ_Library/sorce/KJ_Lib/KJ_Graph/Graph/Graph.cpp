#include "Graph.h"
#include "../../KJ_GenericPrg/KJ_GenericPrg.h"
#include <queue>

using namespace std;

namespace Klibrary{
	template<class Node, class Edge>
	void BaseGraph<Node, Edge>::Release(){

		vector<Node*>::iterator nodeIterator;
		for (nodeIterator = m_nodes.begin(); nodeIteratorc != m_nodes.end(); nodeIterator++){
			K_SAFE_DELETE(*nodeIterator);
		}

		vector<Edge>::iterator edgeIterator;
		for (edgeIterator = m_edges.begin(); edgeIterator != m_edges.end(); edgeIterator++){
			K_SAFE_DELETE(*edgeIterator);
		}
		
		m_edges.clear;
		m_nodes.clear;
	}

	template<class Node, class Edge>
	bool BaseGraph<Node, Edge>::CreateEdge(Node* head, Node* terminus, bool isTwoWay = true){
		Edge* edge = new Edge();
		edge->SetHead(head);
		edge->SetTerminus(terminus);
		terminus->AddEdge(edge);

		if (isTwoWay){
			Edge* edge2 = new Edge();
			edge2->SetHead(terminus);
			edge2->SetTerminus(head);
			head->AddEdge(edge2);
		}

	}

	template<class Node, class Edge>
	void BaseGraph<Node, Edge>::InitializePath(){
		vector<Node *>::iterator ite;
		for (ite = m_nodes.begin(); ite != m_nodes.end(); ite++){
			(*ite)->SetSearchCost(FLT_MAX);
			(*ite)->SetLead(nullptr);
		}
	}

	//この関数が呼び出される度にコスト換算がされ、最短経路が検出される。
	//この関数が呼ばれる時点ではすべてのノードにコストは設定されていない。
	//接続されているエッジからコストを算出してそれをノードに格納する。
	//そのノードを低コスト順にリストに格納する。
	//Aスターでの検索ではないので時間はかかる。
	template<class Node, class Edge>
	float BaseGraph<Node, Edge>::ComputeBestPath(Node* start, Node* goal, float*(fpCostFunc)(Edge *), vector<Node>& path){
		
		InitializePath();

		//ここにコストが低い順でノードを格納する。
		//GraphNodeSerchCostComparerのoperatorでソートされる。
		priority_queue<Node*, vector<Node*>, GraphNodeSerchCostComparer> searchCostListAs;

		start->SetSearchCost(0);
		Node* currentNode = start; //開始ノード設定
		searchCostListAs.push(start); //Queue上で探索を開始する。
		float totalCostToGoal = FLT_MAX;
		

		vector<Edge*>::iterator edgeIte;
		Edge* connectedEdge;  //接続している辺
		Node* neighboringNode;  //近隣のノード
		float edgeCost = 0;
		float newCostToNeighboringNode = 0;
		float currentCostToNeighboringNode = 0;
		while (!searchCostListAs.empty()){
			const vector<Edge*> &edges = currentNode->GetEdges(); //参照を受け取っているので毎回初期化で入れるしかない。

			for (edgeIte = edges.begin(); edgeIte != edges.end(); edgeIte++){
				connectedEdge = (*edgeIte); //接続しているエッジ取り出し
				neighboringNode = static_cast<Node*>(connectedEdge->GetHead()); //エッジ接続先のノード

				if (neighboringNode == currentNode->GetLead())continue; //すでに計算済みなので飛ばし

				edgeCost = fpCostFunc(connectedEdge);   //エッジコスト換算
				currentCostToNeighboringNode = neighboringNode->GetSerchCost();
				newCostToNeighboringNode = currentNode->GetSearchCost() + edgeCost;


				//SerchCostはstart以外FLT_MAXで初期化、totalCostはFLT_MAXで初期化されている。
				if (newCostToNeighboringNode < currentCostToNeighboringNode &&
					newCostToNeighboringNode < totalCostToGoal){
					neighboringNode->SetSearchCost(newCostToNeighboringNode);
					neighboringNode->SetLead(currentNode);
						
					if (neighboringNode == goal){
						totalCostToGoal = newCostToNeighboringNode;
					}

					searchCostListAs.push(neighboringNode);
				}
			}//for
			
			searchCostListAs.pop();
			if (!searchCostListAs.empty()){
				currentNode = searchCostListAs.top(); //常に前のノードからみて最低コストのノードが次のリードノードに選ばれる。
			}
		}//while


		//最短経路データ格納
		//goalのリーダから辿って格納するだけ。
		if (totalCostToGoal < FLT_MAX){
			Node* pathNode = goal;

			do{
				path.push_back(pathNode);
				pathNode = static_cast<Node*>(pathNode->GetLead());
			} while (pathNode != start);
			
			path.push_back(start);
			
		}
		return totalCostToGoal;
	}
	 
}//namespace