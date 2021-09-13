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

#include "HiddenComponent.h"

namespace basecross {

	//auto text = to_wstring(numDelete);
	//MessageBox(0, text.c_str(), L"test", 0);

	Vec3 GraphAstar::CalucTargetNode(const std::shared_ptr<GameObject>& objPtr) {
		if (m_shortRoutes.size() == 0) {
			m_isRouteEnd = true;
		}

		if (m_isRouteEnd) {
			return Vec3(0.0f);
		}

		//オブジェクトが探索ノードの近くにいたら、次のノードに切り替える。
		float nearRange = 2.0f;  //近くと判断される距離

		auto trans = objPtr->GetComponent<Transform>();
		auto objPos = trans->GetPosition();

		auto nodePos = m_shortRoutes[m_routeIndex].nextNode->GetPosition();  //現在の目標ノードのポジションを取得

		auto toNode = nodePos - objPos;
		if (toNode.length() <= nearRange) {  //ノードの近くまで来たら。
			m_routeIndex++;
		}

		//ノードインデックスがショートを超えたら
		if (m_shortRoutes.size() <= m_routeIndex) {
			m_isRouteEnd = true;//機能をoffにする。
		}

		return nodePos;
	}

	void GraphAstar::SearchAstarStart(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target) {
		auto selfNearNode = UtilityAstar::SearchNearNode(*this, self);
		auto targetNearNode = UtilityAstar::SearchNearNode(*this, target);
		SearchAstarStart(selfNearNode, targetNearNode);
	}

	void GraphAstar::SearchAstarStart(const std::shared_ptr<GameObject>& self, const Vec3& targetPos) {
		auto selfNearNode = UtilityAstar::SearchNearNode(*this, self);
		auto targetNearNode = UtilityAstar::SearchNearNode(*this, targetPos);
		SearchAstarStart(selfNearNode, targetNearNode);
	}

	void GraphAstar::SearchAstarStart(const Vec3& selfPos, const Vec3& targetPos) {
		auto selfNearNode = UtilityAstar::SearchNearNode(*this,selfPos);
		auto targetNearNode = UtilityAstar::SearchNearNode(*this,targetPos);
		SearchAstarStart(selfNearNode, targetNearNode);
	}

	void GraphAstar::SearchAstarStart(const std::shared_ptr<NavGraphNode>& selfNearNode, const std::shared_ptr<NavGraphNode>& targetNearNode) {
		ResetAstar();

		m_heuristic.SetTargetNode(targetNearNode);  //ヒューリスティック関数に目標ノードを設定

		if (selfNearNode->GetPosition() == targetNearNode->GetPosition()) {
			m_shortRoutes.push_back(AstarExpectData(selfNearNode, targetNearNode, 0, 0));
			return;
		}

		//ループして処理を行う。
		LoopSearchAstar(selfNearNode);
	}

	const std::shared_ptr<const NavGraphNode> GraphAstar::GetBeforeNode() const {
		if (m_shortRoutes.size() != 0) {
			auto index = m_shortRoutes.size() - 1;
			return m_shortRoutes[index].node.GetShard();
		}

		return nullptr;
	}

	bool GraphAstar::IsAstarEnd() {
		//最終的に判断する方法を変える。
		auto index = m_shortRoutes.size() - 1;

		//限りなく目的地に近いならtrue
		float nearRange = 0.1f;
		if (m_shortRoutes[index].heuristic <= nearRange) {
			return true;
		}
		else {
			return false;
		}
	}

	bool GraphAstar::IsRouteLoop(const AstarExpectData& shortRoute) {
		for (auto& route : m_shortRoutes) {
			if (route.node == shortRoute.nextNode) {
				return true;
			}
		}

		return false;
	}

	bool GraphAstar::IsShortRoute(const AstarExpectData& shortRoute) {
		//sizeが0の場合は処理を行わない
		if (m_shortRoutes.size() == 0) {
			return true;
		}

		auto beforeIndex = m_shortRoutes.size() - 1;
		auto beforeRoute = m_shortRoutes[beforeIndex];

		//送られてきたデータが前回分より小さければtrue
		if (beforeRoute.GetSumRange() >= shortRoute.GetSumRange()) {
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
		auto edges = m_graph->GetEdges(beforeShort.node->GetIndex());
		for (auto& edge : edges) {
			if (newShortRoute.nextNode->GetIndex() == edge.GetTo()) {
				//ノードを戻る処理		
				return true;
			}
		}

		return false;
	}

	void GraphAstar::ResetAstar() {
		m_isRouteEnd = false;
		m_routeIndex = 0;
		m_expectDatas.clear();
		m_shortRoutes.clear();
	}

	void GraphAstar::RemoveData(const AstarExpectData& data) {
		auto index = data.node->GetIndex();

		//デバッグ用
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
		//合計の長さが一緒のデータを削除
		while (iter != m_expectDatas[index].end()) {
			if (iter->GetSumRange() == data.GetSumRange()) {
				//if (iter->nextNode == data.nextNode) {
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

	void GraphAstar::NextProcess(const AstarExpectData& newRoute) {
		m_shortRoutes.push_back(newRoute);
	}

	void GraphAstar::BackProcess(const AstarExpectData& shortRoute) {
		//前回分から最少の部分を省く
		RemoveData(shortRoute);
		//最後のショートルートの削除
		BackShortRoute();
	}

	void GraphAstar::LoopSearchAstar(const std::shared_ptr<NavGraphNode>& initialNode) {
		int tempIndex = 0;
		int maxTempIndex = 100000;
		//強制終了のバグなくなったら消す。
		while(tempIndex < maxTempIndex){
			tempIndex++;
			std::shared_ptr<NavGraphNode> startNode;
			if (m_shortRoutes.size() == 0) {  //最初の時のみ
				startNode = initialNode;
			}
			else {
				auto index = m_shortRoutes.size() - 1;
				startNode = m_shortRoutes[index].nextNode.GetShard();
			}

			//初めに、全ての隣接ノードの期待値を測る。
			auto datas = CalucNearNodeExpectData(startNode);

			//ノードが一つもない場合は「処理を飛ばして」BackProcessをする。
			if (datas.size() == 0) {
				auto index = (int)m_shortRoutes.size() - 1;
				if (index < 0) {
					int temp = 0;
					break;
				}
				BackProcess(m_shortRoutes[index]);  //検索するノードがないため、一番最初に戻る。
				continue;
			}

			//それぞれの合計の中で一番小さい理想値を求める。
			auto shortRoute = CalucMinRangeNode(datas);
			
			//選んだノードが被っていた場合。ループする可能性があるため
			if(IsRouteLoop(shortRoute)){
				BackProcess(shortRoute);
				continue;
			}

			//一番最初に選んだノードが最短かどうか判断する。
			//そうでない場合は処理を一回もどす。
			if (IsShortRoute(shortRoute)) {
				NextProcess(shortRoute);

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
					NextProcess(shortRoute);  //次に進む。

					if (IsAstarEnd()) {  //検索終了
						break;
					}
				}
			}
		}

		LastAdjust(initialNode);

		//デバッグ
		if (tempIndex >= maxTempIndex) {
			DebugObject::sm_wss << endl << L"serchOver" << endl;
		}

		for (auto route : m_shortRoutes) {
			DebugObject::AddValue(route.nextNode->GetIndex(),false);
			DebugObject::AddString(L",",false);
		}
	}

	std::vector<AstarExpectData> GraphAstar::CalucNearNodeExpectData(const std::shared_ptr<NavGraphNode>& node) {
		//一度検索したことのあるノードはその分を返す
		if (m_expectDatas.count(node->GetIndex())) {
			return m_expectDatas[node->GetIndex()];
		}

		//エッジの距離を測って配列で返す。
		auto selfPos = node->GetPosition();
		auto index = node->GetIndex();
		auto edges = m_graph->GetEdges(index);

		std::vector<AstarExpectData> reExpectData;  //リターンする期待値を含むデータ。

		auto beforeNode = GetBeforeNode();

		for (auto edge : edges) {
			auto toIndex = edge.GetTo();
			auto nextNode = m_graph->GetNode(toIndex);

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

		m_expectDatas[node->GetIndex()] = reExpectData;
		return reExpectData;
	}

	float GraphAstar::CalucNearNodeRange(const std::shared_ptr<NavGraphNode>& selfNode, const std::shared_ptr<NavGraphNode>& targetNode) {
		auto selfPos = selfNode->GetPosition();
		auto targetPos = targetNode->GetPosition();

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

	void GraphAstar::LastAdjust(const std::shared_ptr<NavGraphNode>& initialNode) {
		auto shortRoutes = m_shortRoutes;
		m_shortRoutes.clear();
		m_shortRoutes.push_back(AstarExpectData(initialNode,initialNode,0,0));
		for (auto route : shortRoutes) {
			m_shortRoutes.push_back(route);
		}
	}

	//アクセッサ------------------------------------------------------------------------------------------------------

	int GraphAstar::AddNode(const Vec3& position) {
		//仮の対象に入れないオブジェクト
		vector<shared_ptr<GameObject>> excluteObjs;
		maru::MyUtility::AddComponents<HiddenComponent>(excluteObjs);

		return AddNode(position, MyUtility::GetStage()->GetGameObjectVec(), excluteObjs);
	}

	int GraphAstar::AddNode(const Vec3& position,
		const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs)
	{
		//ノードの生成
		auto index = m_graph->GetNextFreeNodeIndex();
		auto newNode = make_shared<NavGraphNode>(index, position);

		auto edges = UtilityAstar::CreateAdjacendEdges(m_graph, newNode, obstacleObjs, excluteObjs);

		//現在はエッジが作成されたときのみ生成するようにする。(繋がってないノードを対象にした場合に処理が止まってしまうため。)
		//改善され次第外す。
		if (edges.size() != 0) {
			//ノードの追加
			m_graph->AddNode(newNode);
		}

		return index++;
	}

	void GraphAstar::RemoveNode(const int& index) {
		m_graph->RemoveNode(index);
	}

	void GraphAstar::AddEdges(const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs) {
		auto nodes = m_graph->GetNodes();
		for (auto& node : nodes) {
			auto edges = UtilityAstar::CreateAdjacendEdges(m_graph, node, obstacleObjs, excluteObjs);
			if (edges.size() == 0) {
				//ノードの追加
				m_graph->RemoveNode(node->GetIndex());
			}
		}
	}
}

//endbasecross