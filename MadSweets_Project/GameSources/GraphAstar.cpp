/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "GraphAstar.h"
#include "DebugObject.h"


namespace basecross {

	void GraphAstar::RemoveData(const AstarExpectData& data) {
		auto index = m_expectDatas.size() - 1;
		auto iter = m_expectDatas[index].begin();

		while (iter != m_expectDatas[index].end()) {
			if (iter->GetSumRange() == data.GetSumRange()) {
				m_expectDatas[index].erase(iter);
				return;
			}
		}
	}

	void GraphAstar::BackShortRoute() {
		auto end = m_shortRoutes.end();
		m_shortRoutes.erase(end);
	}

	bool GraphAstar::IsAstarEnd() {
		//最終的に判断する方法を変える。
		auto index = m_shortRoutes.size() - 1;

		if (m_shortRoutes[index].heuristic <= 0.1f){
			return true;
		}
		else {
			return false;
		}
	}

	NavGraphNode GraphAstar::SearchNearNode(const std::shared_ptr<GameObject>& target) {
		//一番近いノードの検索
		auto nodes = m_graph.GetNodes();
		auto targetTrans = target->GetComponent<Transform>();
		auto targetPos = targetTrans->GetPosition();

		float minRange = 10000.0f;
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
		//m_countIndex = 0;
		m_isRouteEnd = false;
		m_routeIndex = 0;
		auto selfNearNode = SearchNearNode(self);
		auto targetNearNode = SearchNearNode(target);
		DebugObject::AddVector(targetNearNode.GetPosition());
		m_heuristic.SetTargetNode(targetNearNode);  //ヒューリスティック関数に目標ノードを設定

		//ループして処理を行う。
		LoopSearchAstar(selfNearNode);
	}

	void GraphAstar::LoopSearchAstar(const NavGraphNode& stdNode) {
		//次にそれを基準に同じ行程を踏む。
		//int count = 0;
		while (true) {
			NavGraphNode node;
			if (m_shortRoutes.size() == 0) {  //最初の時のみ
				node = stdNode;
			}
			else {
				auto index = m_shortRoutes.size() - 1;
				node = m_shortRoutes[index].nextNode;
			}

			//初めに、全ての隣接ノードの期待値を測る。
			auto datas = CalucNearNodeExpectData(node);
			//それぞれの合計の中で一番小さい理想値を求める。
			auto shortRoute = CalucMinRangeNode(datas);
			DebugObject::AddVector(shortRoute.nextNode.GetPosition());
			
			//一番最初に選んだノードが最短かどうか判断する。
			//そうでない場合は処理を一回もどす。
			if (IsShortRoute(shortRoute)) {
				m_shortRoutes.push_back(shortRoute);
				m_expectDatas.push_back(datas);
				m_isCreateNewData = true;

				if (IsAstarEnd()) {  //検索終了
					break;
				}
			}
			else {
				//前回分から最少の部分を省く
				RemoveData(shortRoute);
				//前回の分から最少のデータを求める
				BackShortRoute();
				//最少のデータからまた最少ルート検索
			}
		}
	}

	std::vector<AstarExpectData> GraphAstar::CalucNearNodeExpectData(const NavGraphNode& node) {
		if (m_isCreateNewData == false) {  //新しい物を作らなくて良いのなら
			int index = (int)m_expectDatas.size() - 1;
			return m_expectDatas[index];  //前回分のインデックスを返す。
		}

		//エッジの距離を測って配列で返す。
		auto selfPos = node.GetPosition();
		auto index = node.GetIndex();
		auto edges = m_graph.GetEdges(index);

		std::vector<AstarExpectData> reExpectData;  //リターンする期待値を含むデータ。

		for (auto edge : edges) {
			auto toIndex = edge.GetTo();
			auto nextNode = m_graph.GetNode(toIndex);

			auto toRange = CalucNearNodeRange(node,nextNode);
			auto toHeuriRange = m_heuristic.CalucHeuristicRange(nextNode);  //候補ノードから目的ノードまでのヒューリスティック距離を求める。

			AstarExpectData data(node,nextNode,toRange,toHeuriRange);
			reExpectData.push_back(data);
		}

		m_isCreateNewData = false;
		return reExpectData;
	}

	float GraphAstar::CalucNearNodeRange(const NavGraphNode& selfNode, const NavGraphNode& targetNode) {
		auto selfPos = selfNode.GetPosition();
		auto targetPos = targetNode.GetPosition();

		auto toVec = targetPos - selfPos;
		return toVec.length();
	}

	AstarExpectData GraphAstar::CalucMinRangeNode(const std::vector<AstarExpectData>& datas) {
		//現状だときちんとしたインデックスを取得できていない。
		int index = 0;
		float minRange = 100000.0f;
		for (int i = 0; i < datas.size(); i++) {
			auto range = datas[i].GetSumRange();
			if (range < minRange) {
				minRange = range;
				index = i;
			}
		}

		return datas[index];
	}

	bool GraphAstar::IsShortRoute(const AstarExpectData& data) {
		//sizeが0の場合は処理を行わない
		if (m_shortRoutes.size() == 0) {
			return true;
		}

		auto beforeIndex = m_shortRoutes.size() - 1;
		auto beforeRoute = m_shortRoutes[beforeIndex];

		//送られてきたデータが前回分より小さければtrue
		if (beforeRoute.GetSumRange() >= data.GetSumRange()) {
			return true;
		}
		else {
			return false;
		}
	}

	Vec3 GraphAstar::CalucTargetNode(const std::shared_ptr<GameObject>& objPtr) {
		//m_isRouteEnd = true;
		//DebugObject::m_wss.str(L"");
		if (m_isRouteEnd) {
			//DebugObject::m_wss << to_wstring(m_shortRoutes.size());
			return Vec3(0.0f);
		}

		//オブジェクトが探索ノードの近くにいたら、次のノードに切り替える。
		float nearRange = 0.1f;  //近くと判断される距離

		auto trans = objPtr->GetComponent<Transform>();
		auto objPos = trans->GetPosition();
		
		auto nodePos = m_shortRoutes[m_routeIndex].nextNode.GetPosition();  //現在の目標ノードのポジションを取得
		//DebugObject::AddVector(nodePos);

		auto toNode = nodePos - objPos;
		if (toNode.length() <= nearRange) {  //ノードの近くまで来たら。
			m_routeIndex++;
		}

		//ノードインデックスがショートを超えたら。
		if (m_shortRoutes.size() <= m_routeIndex) {
			m_isRouteEnd = true;//機能をoffにする。
		}

		return nodePos;
	}
}

//endbasecross