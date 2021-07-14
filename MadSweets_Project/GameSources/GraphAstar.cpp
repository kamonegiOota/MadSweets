/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "GraphAstar.h"

namespace basecross {

	NavGraphNode GraphAstar::SearchNearNode(const std::shared_ptr<GameObject>& target) {
		//一番近いノードの検索
		auto nodes = m_graph.GetNodes();
		auto targetTrans = target->GetComponent<Transform>();
		auto targetPos = targetTrans->GetPosition();

		float minRange = 0.0f;
		NavGraphNode minNode;  //一番距離が短いノード

		//検索開始
		for (const auto& node : nodes) {
			auto pos = node.GetPosition();
			auto toNode = pos - targetPos;
			const auto& range = toNode.length();

			//距離が短かったらこれにする。
			if (range <= minRange) {
				minRange = range;
				minNode = node;
			}
		}

		return minNode;
	}

	void GraphAstar::SearchAstarStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target) {
		m_rangeIndex = 0;
		auto selfNearNode = SearchNearNode(self);
		auto targetNearNode = SearchNearNode(target);
		m_heuristic.SetTargetNode(targetNearNode);  //ヒューリスティック関数に目標ノードを設定
		m_shortNodes.push_back(selfNearNode);  //スタート位置のノードのインデックスの格納

		//次にそれを基準に同じ行程を踏む。
		while (true) {
			auto node = m_shortNodes[m_rangeIndex];

			//初めに、全ての隣接ノードの長さを測る。
			auto toRanges = CalucNearNodeSumRange(node);
			m_nodeRanges.push_back(toRanges);  //その合計をnodeRangesに格納

			//それぞれの合計の中で一番小さい理想値を求める。
			auto minRangeNode = CalucMinRangeNode(toRanges);
			m_shortNodes.push_back(minRangeNode);

			//一番最初に選んだノードが最短かどうか判断する。
			//そうでない場合は処理を一回もどす。
			//もし進む場合はインデックスを進める。
			
		}
	}

	std::vector<float> GraphAstar::CalucNearNodeSumRange(const NavGraphNode& node) {
		//エッジの距離を測って配列で返す。
		auto selfPos = node.GetPosition();
		auto index = node.GetIndex();
		auto edges = m_graph.GetEdges(index);

		std::vector<float> reRanges;  //リターンする距離を配列でまとめる変数。

		for (auto edge : edges) {
			auto toIndex = edge.GetTo();
			auto nextNode = m_graph.GetNode(toIndex);

			auto toRange = CalucNearNodeRange(node,nextNode);
			auto toHeuriRange = m_heuristic.CalucHeuristicRange(nextNode);  //候補ノードから目的ノードまでのヒューリスティック距離を求める。

			auto sumValue = toRange + toHeuriRange;  //レンジとヒューリスティック距離の合計
			reRanges.push_back(sumValue);
		}

		return reRanges;
	}

	float GraphAstar::CalucNearNodeRange(const NavGraphNode& selfNode, const NavGraphNode& targetNode) {
		auto selfPos = selfNode.GetPosition();
		auto targetPos = targetNode.GetPosition();

		auto toVec = targetPos - selfPos;
		return toVec.length();
	}

	NavGraphNode GraphAstar::CalucMinRangeNode(const std::vector<float>& ranges) {
		//現状だときちんとしたインデックスを取得できていない。
		int index = 0;
		float minRange = 0.0f;
		for (int i = 0; i < ranges.size(); i++) {
			if (ranges[i] <= minRange) {
				minRange = ranges[i];
				index = i;
			}
		}

		return m_graph.GetNode(index);
	}

}

//endbasecross