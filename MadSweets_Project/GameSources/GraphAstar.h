/*!
@file GraphNode.h
@brief GraphNode�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once
#include "stdafx.h"

#include "SparseGraph.h"
#include "Heuristic.h"

namespace basecross {

	/// <summary>
	/// Astar�ɂ�����A���Ғl�̌v�Z�ɗp����\����
	/// </summary>
	struct AstarExpectData {
		NavGraphNode node = NavGraphNode();
		float range = 0.0f;
		float heuristic = 0.0f;
	};

	class GraphAstar
	{
		/// <summary>
		/// �m�[�h�ƃG�b�W���Ǘ�����
		/// </summary>
		SparseGraph<NavGraphNode, GraphEdge> m_graph;
		/// <summary>
		/// �q���[�X���b�N�v�Z�����Ă����N���X
		/// </summary>
		Heuristic m_heuristic;

		std::vector<std::vector<float>> m_nodeRanges;  //�v�������m�[�h�Ԃ̒������i�[����B
		int m_rangeIndex;  //���ݒT���v�Z������ڂ��𔻒f����B

		std::vector<NavGraphNode> m_shortNodes;  //�ŒZ�m�[�h���i�[�����z��B

	public:
		GraphAstar(const SparseGraph<NavGraphNode, GraphEdge>& graph)
			:m_graph(graph),m_rangeIndex(0)
		{}

		//�ړI�m�[�h�̐ݒ�
		//�^�[�Q�b�g�����ԋ߂��̃m�[�h����������B
		NavGraphNode SearchNearNode(const std::shared_ptr<GameObject>& target);
		
		//�����m�[�h�ƃG�b�W����A�ǂ̃��[�g����ԋ߂�������
		void SearchAstarStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target);

		//�אڃm�[�h�̋����ƃq���[���X�e�B�b�N�����̍��v�𑪂�
		std::vector<float> CalucNearNodeSumRange(const NavGraphNode& node);

		//�אڃm�[�h�̋����𑪂�
		float CalucNearNodeRange(const NavGraphNode& fromNode, const NavGraphNode& toNode);

		//�v�������אڃm�[�h�̊��Ғl�̒���,��ԏ��������̃m�[�h�����������B
		NavGraphNode CalucMinRangeNode(const std::vector<float>& ranges);

		//���߂��������{���ɍŒZ���ǂ����𔻒f����B
		bool IsShortRoot();
	};

}

//endbasecross