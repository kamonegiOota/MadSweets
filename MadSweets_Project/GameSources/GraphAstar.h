/*!
@file GraphNode.h
@brief GraphNode�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once
#include "stdafx.h"
#include "SparseGraph.h"

namespace basecross {

	class GraphAstar
	{
		/// <summary>
		/// �m�[�h�ƃG�b�W���Ǘ�����
		/// </summary>
		SparseGraph<NavGraphNode, GraphEdge> m_graph;

		

	public:
		GraphAstar(const SparseGraph<NavGraphNode, GraphEdge>& graph)
			:m_graph(graph)
		{}

		//�ړI�m�[�h�̐ݒ�
		//�^�[�Q�b�g�����ԋ߂��̃m�[�h����������B
		void SearchNearNode(const std::shared_ptr<GameObject>& target) {

		}
		
		//


	};

}

//endbasecross