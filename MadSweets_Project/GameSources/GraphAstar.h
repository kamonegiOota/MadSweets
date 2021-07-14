/*!
@file GraphNode.h
@brief GraphNodeなど
担当者：丸山 裕喜
*/

#pragma once
#include "stdafx.h"

#include "SparseGraph.h"
#include "Heuristic.h"

namespace basecross {

	/// <summary>
	/// Astarにおける、期待値の計算に用いる構造体
	/// </summary>
	struct AstarExpectData {
		NavGraphNode node = NavGraphNode();
		float range = 0.0f;
		float heuristic = 0.0f;
	};

	class GraphAstar
	{
		/// <summary>
		/// ノードとエッジを管理する
		/// </summary>
		SparseGraph<NavGraphNode, GraphEdge> m_graph;
		/// <summary>
		/// ヒュースリック計算をしてくれるクラス
		/// </summary>
		Heuristic m_heuristic;

		std::vector<std::vector<float>> m_nodeRanges;  //計測したノード間の長さを格納する。
		int m_rangeIndex;  //現在探索計算が何回目かを判断する。

		std::vector<NavGraphNode> m_shortNodes;  //最短ノードを格納した配列。

	public:
		GraphAstar(const SparseGraph<NavGraphNode, GraphEdge>& graph)
			:m_graph(graph),m_rangeIndex(0)
		{}

		//目的ノードの設定
		//ターゲットから一番近くのノードを検索する。
		NavGraphNode SearchNearNode(const std::shared_ptr<GameObject>& target);
		
		//自分ノードとエッジから、どのルートが一番近いか検索
		void SearchAstarStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target);

		//隣接ノードの距離とヒューリスティック距離の合計を測る
		std::vector<float> CalucNearNodeSumRange(const NavGraphNode& node);

		//隣接ノードの距離を測る
		float CalucNearNodeRange(const NavGraphNode& fromNode, const NavGraphNode& toNode);

		//計測した隣接ノードの期待値の中で,一番小さい数のノードを引き抜く。
		NavGraphNode CalucMinRangeNode(const std::vector<float>& ranges);

		//求めた距離が本当に最短かどうかを判断する。
		bool IsShortRoot();
	};

}

//endbasecross