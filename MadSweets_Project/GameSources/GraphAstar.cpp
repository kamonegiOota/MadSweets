/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "GraphAstar.h"
#include "DebugObject.h"
#include "MyUtility.h"
#include "UtilityAstar.h"

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
			end--;
			m_expectDatas.erase(end);
			index--;
		}

		if (m_expectDatas.size() == 0) {
			int i = 0;
		}

		if (m_expectDatas[index].size() == 0) {
			int i = 0;
		}

		if (index <= 0) {
			int i = 0;
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
		if (index < 0) {
			int i = 0;
		}

		if (m_shortRoutes[index].heuristic <= 0.1f){
			return true;
		}
		else {
			return false;
		}
	}

	void GraphAstar::SearchAstarStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target) {
		auto targetPos = target->GetComponent<Transform>()->GetPosition();
		SearchAstarStart(self, targetPos);
	}

	void GraphAstar::SearchAstarStart(const std::shared_ptr<GameObject>& self, const Vec3& targetPos) {
		//m_selfObj = self;
		auto selfPos = self->GetComponent<Transform>()->GetPosition();
		SearchAstarStart(selfPos,targetPos);
	}

	void GraphAstar::SearchAstarStart(const Vec3& selfPos, const Vec3& targetPos) {
		ResetAstar();

		auto selfNearNode = UtilityAstar::SearchNearNode(*this,selfPos);
		DebugObject::m_wss << L"stattNode:" << to_wstring(selfNearNode.GetIndex()) << endl;
		auto targetNearNode = UtilityAstar::SearchNearNode(*this,targetPos);
		//DebugObject::AddVector(targetNearNode.GetPosition());
		m_heuristic.SetTargetNode(targetNearNode);  //ヒューリスティック関数に目標ノードを設定

		if (selfNearNode.GetPosition() == targetNearNode.GetPosition()) {
			m_shortRoutes.push_back(AstarExpectData(selfNearNode, targetNearNode, 0, 0));
			return;
		}

		//ループして処理を行う。
		AstarExpectData data;
		data.nextNode = selfNearNode;
		LoopSearchAstar(data);
	}

	void GraphAstar::SearchAstarForecastStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target) {
		m_isForecase = true;

		auto targetPos = target->GetComponent<Transform>()->GetPosition();

	    auto targetNearNode = UtilityAstar::SearchNearNode(*this,target);
		auto startNodePos = targetNearNode.GetPosition();
		auto toTargetVec = targetPos - startNodePos;
		toTargetVec.y = 0.0f;

		//ターゲットノードの計算
		auto targetNode = UtilityAstar::CalucTargetDirectNode(*this,targetNearNode,targetPos);

		SearchAstarStart(targetPos, targetNode.GetPosition());
	}

	void GraphAstar::ResetAstar() {
		m_isRouteEnd = false;
		m_routeIndex = 0;
		m_expectDatas.clear();
		m_shortRoutes.clear();
		m_isCreateNewData = true;
		m_isReturnPhase = false;
	}

	void GraphAstar::LastAdjust(const AstarExpectData& startData) { //最終調整
		//初期ノードと次のノードの間に自分がいる場合は処理をしない
		//if (m_selfObj) {
		//	auto startPos = startData.nextNode.GetPosition();
		//	auto nextPos = m_shortRoutes[0].nextNode.GetPosition();
		//	if (maru::MyUtility::IsRayObstacle(startPos, nextPos, m_selfObj) == false) {  //自分の間に二つのノードが存在しなかったら
		//		return;
		//	}
		//}

		if (!m_isForecase) {  //予測状態出なかったら処理をしない
			return;
		}
		m_isForecase = false;

		vector<AstarExpectData> newShortRoutes;
		newShortRoutes.push_back(startData);

		for (const auto& route : m_shortRoutes) {
			newShortRoutes.push_back(route);
		}

		m_shortRoutes = newShortRoutes;
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

	void GraphAstar::LoopSearchAstar(const AstarExpectData& startData) {
		//for (int i = 0; i < 5; i++) {
		while(true){
			NavGraphNode node;
			if (m_shortRoutes.size() == 0) {  //最初の時のみ
				node = startData.nextNode;
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
				if (index < 0) {
					break;
				}
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

		LastAdjust(startData);

		for (auto route : m_shortRoutes) {
			DebugObject::m_wss << route.nextNode.GetIndex() << L",";
		}
	}

	std::vector<AstarExpectData> GraphAstar::CalucNearNodeExpectData(const NavGraphNode& node) {
		if (m_isCreateNewData == false) {  //新しい物を作らなくて良いのなら
			int index = (int)m_expectDatas.size() - 1;
			if (index < 0) {
				int i = 0;
			}
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
		//直前でデータが0の時の処理をしているため、エラー回避はいらない。
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
		if (beforeIndex < 0) {
			int i = 0;
		}

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
		if (m_shortRoutes.size() == 0) {  //エラーが発覚したらこのifいらないかも
			return false;
		}

		auto index = (int)m_shortRoutes.size() - 1;
		if (index < 0) {
			int i = 0;
		}
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

		if (m_shortRoutes.size() == 0) {
			m_isRouteEnd = true;
		}

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

		//ノードインデックスがショートを超えたら
		if (m_shortRoutes.size() <= m_routeIndex) {
			m_isRouteEnd = true;//機能をoffにする。
		}

		//DebugObject::m_wss << to_wstring(m_shortRoutes[m_routeIndex].node.GetIndex());
		return nodePos;
	}
}

//endbasecross