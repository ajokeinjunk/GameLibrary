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

	//���̊֐����Ăяo�����x�ɃR�X�g���Z������A�ŒZ�o�H�����o�����B
	//���̊֐����Ă΂�鎞�_�ł͂��ׂẴm�[�h�ɃR�X�g�͐ݒ肳��Ă��Ȃ��B
	//�ڑ�����Ă���G�b�W����R�X�g���Z�o���Ă�����m�[�h�Ɋi�[����B
	//���̃m�[�h���R�X�g���Ƀ��X�g�Ɋi�[����B
	//A�X�^�[�ł̌����ł͂Ȃ��̂Ŏ��Ԃ͂�����B
	template<class Node, class Edge>
	float BaseGraph<Node, Edge>::ComputeBestPath(Node* start, Node* goal, float*(fpCostFunc)(Edge *), vector<Node>& path){
		
		InitializePath();

		//�����ɃR�X�g���Ⴂ���Ńm�[�h���i�[����B
		//GraphNodeSerchCostComparer��operator�Ń\�[�g�����B
		priority_queue<Node*, vector<Node*>, GraphNodeSerchCostComparer> searchCostListAs;

		start->SetSearchCost(0);
		Node* currentNode = start; //�J�n�m�[�h�ݒ�
		searchCostListAs.push(start); //Queue��ŒT�����J�n����B
		float totalCostToGoal = FLT_MAX;
		

		vector<Edge*>::iterator edgeIte;
		Edge* connectedEdge;  //�ڑ����Ă����
		Node* neighboringNode;  //�ߗׂ̃m�[�h
		float edgeCost = 0;
		float newCostToNeighboringNode = 0;
		float currentCostToNeighboringNode = 0;
		while (!searchCostListAs.empty()){
			const vector<Edge*> &edges = currentNode->GetEdges(); //�Q�Ƃ��󂯎���Ă���̂Ŗ��񏉊����œ���邵���Ȃ��B

			for (edgeIte = edges.begin(); edgeIte != edges.end(); edgeIte++){
				connectedEdge = (*edgeIte); //�ڑ����Ă���G�b�W���o��
				neighboringNode = static_cast<Node*>(connectedEdge->GetHead()); //�G�b�W�ڑ���̃m�[�h

				if (neighboringNode == currentNode->GetLead())continue; //���łɌv�Z�ς݂Ȃ̂Ŕ�΂�

				edgeCost = fpCostFunc(connectedEdge);   //�G�b�W�R�X�g���Z
				currentCostToNeighboringNode = neighboringNode->GetSerchCost();
				newCostToNeighboringNode = currentNode->GetSearchCost() + edgeCost;


				//SerchCost��start�ȊOFLT_MAX�ŏ������AtotalCost��FLT_MAX�ŏ���������Ă���B
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
				currentNode = searchCostListAs.top(); //��ɑO�̃m�[�h����݂čŒ�R�X�g�̃m�[�h�����̃��[�h�m�[�h�ɑI�΂��B
			}
		}//while


		//�ŒZ�o�H�f�[�^�i�[
		//goal�̃��[�_����H���Ċi�[���邾���B
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