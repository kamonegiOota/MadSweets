/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "GraphAstar.h"
#include "DebugObject.h"


namespace basecross {

	const NavGraphNode *GraphAstar::GetBeforeNode() const {
		if (m_shortRoutes.size() != 0) {
			auto index = m_shortRoutes.size() - 1;
			return &m_shortRoutes[index].node;
		}

		return nullptr;
	}

	void GraphAstar::RemoveData(const AstarExpectData& data) {
		auto index = m_expectDatas.size() - 1;
		if (m_isReturnPhase) {  //リターン状態出会った場合は、最新のデータを消す。
			auto end = m_expectDatas.end();
			m_expectDatas.erase(end);
			index--;
		}

		auto iter = m_expectDatas[index].begin();
		
		while (iter != m_expectDatas[index].end()) {
			if(iter->GetSumRange() == data.GetSumRange()){
				m_expectDatas[index].erase(iter);
				return;
			}
			iter++;
		}
	}

	void GraphAstar::BackShortRoute() {
		auto end = m_shortRoutes.end();
		end--;
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
		auto targetTrans = target->GetComponent<Transform>();
		auto targetPos = targetTrans->GetPosition();

		auto reNode = SearchNearNode(targetPos);
		return reNode;
	}

	NavGraphNode GraphAstar::SearchNearNode(const Vec3& targetPos) {
		auto nodes = m_graph.GetNodes();

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
		auto targetPos = target->GetComponent<Transform>()->GetPosition();
		SearchAstarStart(self, targetPos);
	}

	void GraphAstar::SearchAstarStart(const std::shared_ptr<GameObject>& self, const Vec3& targetPos) {
		m_isRouteEnd = false;
		m_routeIndex = 0;
		m_expectDatas.clear();
		m_shortRoutes.clear();
		m_isCreateNewData = true;
		m_isReturnPhase = false;

		auto selfNearNode = SearchNearNode(self);
		auto targetNearNode = SearchNearNode(targetPos);
		//DebugObject::AddVector(targetNearNode.GetPosition());
		m_heuristic.SetTargetNode(targetNearNode);  //ヒューリスティック関数に目標ノードを設定

		//ループして処理を行う。
		LoopSearchAstar(selfNearNode);
	}

	void GraphAstar::SearchAstarForecastStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target) {
		auto targetPos = target->GetComponent<Transform>()->GetPosition();

		auto targetNearNode = SearchNearNode(target);
		auto startNodePos = targetNearNode.GetPosition();
		auto toTargetVec = targetPos - startNodePos;
		toTargetVec.y = 0.0f;

		float minRad = 360.0f;
		NavGraphNode targetNode;
		auto edges = m_graph.GetEdges(targetNearNode.GetIndex());
		for (const auto& edge : edges) {
			auto toIndex = edge.GetTo();
			auto nextNode = m_graph.GetNode(toIndex);
			auto nextPos = nextNode.GetPosition();

			auto toNextNodeVec = nextPos - startNodePos;
			toNextNodeVec.y = 0.0f;

			auto newDot = dot(toTargetVec.GetNormalized(), toNextNodeVec.GetNormalized());
			auto newRad = acosf(newDot);
			if (newRad < minRad) {
				minRad = newRad;
				targetNode = nextNode;
			}
		}

		SearchAstarStart(self, targetNode.GetPosition());
	}

	void GraphAstar::NextProcess(const AstarExpectData& newRoute, const vector<AstarExpectData>& newDatas) {
		m_shortRoutes.push_back(newRoute);
		m_expectDatas.push_back(newDatas);
		m_isCreateNewData = true;
		m_isReturnPhase = false;
	}

	void GraphAstar::BackProcess(const AstarExpectData& shortRoute) {
		//前回分から最少の部分を省く
		RemoveData(shortRoute);
		//前回の分から最少のデータを求める
		BackShortRoute();
		//二回以上戻った場合に判断
		m_isReturnPhase = true;
	}

	void GraphAstar::LoopSearchAstar(const NavGraphNode& stdNode) {
		//次にそれを基準に同じ行程を踏む。
		
		//for (int i = 0; i < 5; i++) {
		while(true){
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

			//ノードが一つもない場合は「処理を飛ばして」戻る
			if (datas.size() == 0) {
				auto index = (int)m_shortRoutes.size() - 1;
				BackProcess(m_shortRoutes[index]);
				continue;
			}

			//それぞれの合計の中で一番小さい理想値を求める。
			auto shortRoute = CalucMinRangeNode(datas);
			//DebugObject::AddVector(shortRoute.nextNode.GetPosition());
			
			//一番最初に選んだノードが最短かどうか判断する。
			//そうでない場合は処理を一回もどす。
			if (IsShortRoute(shortRoute)) {
				NextProcess(shortRoute, datas);

				if (IsAstarEnd()) {  //検索終了
					break;
				}
			}
			else {
				//nextNodeが前のnodeからのエッジを持っているかどうか？
				if (IsBackShort(shortRoute)) {
					BackProcess(shortRoute);  //戻る
				}
				else {
					NextProcess(shortRoute, datas);  //次に進む。

					if (IsAstarEnd()) {  //検索終了
						break;
					}
				}
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

		auto beforeNode = GetBeforeNode();

		for (auto edge : edges) {
			auto toIndex = edge.GetTo();
			auto nextNode = m_graph.GetNode(toIndex);

			//自分の前のノードの場合は入れない
			if (beforeNode) {  //beforeNodeが存在する場合
				if (beforeNode->GetIndex() == toIndex) {
					continue;
				}
			}

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

	bool GraphAstar::IsBackShort(const AstarExpectData& newShortRoute) {
		auto index = (int)m_shortRoutes.size() - 1;
		auto beforeShort = m_shortRoutes[index];
		auto edges = m_graph.GetEdges(beforeShort.node.GetIndex());
		for (auto& edge : edges) {
			if (newShortRoute.nextNode.GetIndex() == edge.GetTo()) {
				//ノードを戻る処理		
				return true;
			}
		}

		return false;
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