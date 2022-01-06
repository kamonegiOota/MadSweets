/*!
@file UtilityAstar.cpp
@brief UtilityAstar実体
*/

#include "UtilityAstar.h"
#include "MyUtility.h"

#include "PlayerObject.h"
#include "BaseEnemy.h"
#include "HiddenComponent.h"

namespace basecross {

	std::shared_ptr<NavGraphNode> UtilityAstar::SearchNearNode(const GraphAstar& astar, const std::shared_ptr<GameObject>& target) {
		vector<std::shared_ptr<GameObject>> excluteObjs;
		excluteObjs.push_back(target);

		auto targetPos = target->GetComponent<Transform>()->GetPosition();
		return SearchNearNode(astar, targetPos, excluteObjs);
	}

	std::shared_ptr<NavGraphNode> UtilityAstar::SearchNearNode(const GraphAstar& astar, const Vec3& targetPos,
		vector<std::shared_ptr<GameObject>> excluteObjs)
	{
		const auto& graph = astar.GetGraph();
		const auto& nodes = graph->GetNodes();

		float minRange = 10000.0f;
		std::shared_ptr<NavGraphNode> minNode;  //一番距離が短いノード


		//障害物の対象外を選択
		MyUtility::AddComponents<BaseEnemy>(excluteObjs);
		MyUtility::AddObjects<PlayerObject>(excluteObjs);
		
		//検索開始
		for (const auto& node : nodes) {
			auto pos = node->GetPosition();
			auto toNode = pos - targetPos;
			const auto& range = toNode.length();

			//障害物が合ったらコンティニュ―
			if (maru::MyUtility::IsRayObstacle(targetPos, pos, excluteObjs)) {
				continue;
			}

			//距離が短かったらこれにする。
			if (range <= minRange) {
				minRange = range;
				minNode = node;
			}
		}

		return minNode;
	}

	std::shared_ptr<NavGraphNode> UtilityAstar::SearchMyNodeToTargetNearNode(const GraphAstar& astar,
		const std::shared_ptr<GameObject>& selfObject, const std::shared_ptr<GameObject>& target)
	{
		//自分自身の近くのノードの検索
		const std::shared_ptr<const NavGraphNode> selfNode = SearchNearNode(astar, selfObject);
		const int from = selfNode->GetIndex();  //そのインデクスの取得

		const auto& graph = astar.GetGraph();
		const auto& edges = graph->GetEdges(from);
		const Vec3 targetPosition = target->GetComponent<Transform>()->GetPosition();

		float minRange = 100000.0f;
		std::shared_ptr<NavGraphNode> nearNode;
		for (auto& edge : edges) {
			int toIndex = edge.GetTo();
			std::shared_ptr<NavGraphNode> toNode = graph->GetNode(toIndex);
			auto toVec = toNode->GetPosition() - targetPosition;
			if (toVec.length() < minRange) {
				nearNode = toNode;
				minRange = toVec.length();
			}
		}

		return nearNode;
	}

	std::shared_ptr<NavGraphNode> UtilityAstar::CalucTargetDirectNode(const GraphAstar& astar,
		const std::shared_ptr<NavGraphNode>& startNode,
		const Vec3& targetPos)
	{
		const auto& graph = astar.GetGraph();
		const auto& edges = graph->GetEdges(startNode->GetIndex());

		auto startNodePos = startNode->GetPosition();
		auto toTargetVec = targetPos - startNodePos;
		
		float minRad = 360.0f;
		std::shared_ptr<NavGraphNode> reNode;
		for (const auto& edge : edges) {
			auto toIndex = edge.GetTo();
			auto nextNode = graph->GetNode(toIndex);
			auto nextPos = nextNode->GetPosition();

			auto toNextNodeVec = nextPos - startNodePos;
			toNextNodeVec.y = 0.0f;

			auto newDot = dot(toTargetVec.GetNormalized(), toNextNodeVec.GetNormalized());
			auto newRad = acosf(newDot);

			if (newRad < minRad) {
				minRad = newRad;
				reNode = nextNode;
			}
		}

		return reNode;
	}

	//逃げるためのノードの検索
	std::shared_ptr<NavGraphNode> UtilityAstar::CalucTargetEscapeDirectNode(const GraphAstar& astar,
		const std::shared_ptr<NavGraphNode>& startNode,
		const Vec3& targetPos)
	{
		const auto& graph = astar.GetGraph();
		const auto& edges = graph->GetEdges(startNode->GetIndex());

		auto startNodePos = startNode->GetPosition();
		auto toTargetVec = targetPos - startNodePos;

		float maxRad = 0.0f;
		std::shared_ptr<NavGraphNode> reNode;
		for (const auto& edge : edges) {
			int toIndex = edge.GetTo();
			std::shared_ptr<NavGraphNode> nextNode = graph->GetNode(toIndex);
			auto nextPos = nextNode->GetPosition();

			auto toNextNodeVec = nextPos - startNodePos;
			toNextNodeVec.y = 0.0f;

			auto newDot = dot(toTargetVec.GetNormalized(), toNextNodeVec.GetNormalized());
			auto newRad = acosf(newDot);

			if (newRad > maxRad) {
				maxRad = newRad;
				reNode = nextNode;
			}
		}

		return reNode;
	}
}

//endbasecross