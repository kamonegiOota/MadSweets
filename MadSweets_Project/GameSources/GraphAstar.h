/*!
@file GraphNode.h
@brief GraphNodeなど
担当者：丸山 裕喜
*/

#pragma once
#include "stdafx.h"
#include "SparseGraph.h"

namespace basecross {

	class GraphAstar
	{
		/// <summary>
		/// ノードとエッジを管理する
		/// </summary>
		SparseGraph<NavGraphNode, GraphEdge> m_graph;

		

	public:
		GraphAstar(const SparseGraph<NavGraphNode, GraphEdge>& graph)
			:m_graph(graph)
		{}

		//目的ノードの設定
		//ターゲットから一番近くのノードを検索する。
		void SearchNearNode(const std::shared_ptr<GameObject>& target) {

		}
		
		//


	};

}

//endbasecross