/*!
@file GraphEdge.cpp
@brief GraphEdge実体
*/

#include "UtilityAstar.h"
#include "MyUtility.h"

#include "PlayerObject.h"
#include "BaseEnemy.h"

namespace basecross {

	NavGraphNode UtilityAstar::SearchNearNode(const GraphAstar& astar, const std::shared_ptr<GameObject>& target) {
		auto targetPos = target->GetComponent<Transform>()->GetPosition();
		return SearchNearNode(astar, targetPos);
	}

	NavGraphNode UtilityAstar::SearchNearNode(const GraphAstar& astar, const Vec3& targetPos) {
		const auto& graph = astar.GetGraph();
		const auto& nodes = graph.GetNodes();

		float minRange = 10000.0f;
		NavGraphNode minNode;  //一番距離が短いノード

		//vector<shared_ptr<GameObject>> obstacleObjs;
		vector<shared_ptr<GameObject>> excluteObjs;

		//障害物の対象外を選択
		MyUtility::AddComponents<BaseEnemy>(excluteObjs);
		MyUtility::AddObjects<PlayerObject>(excluteObjs);

		//検索開始
		for (const auto& node : nodes) {
			auto pos = node.GetPosition();
			auto toNode = pos - targetPos;
			const auto& range = toNode.length();

			//障害物が合ったらコンティニュ―
			//if (maru::MyUtility::IsRayObstacle(pos, targetPos, excluteObjs)) {
			//	continue;
			//}

			//距離が短かったらこれにする。
			if (range <= minRange) {
				minRange = range;
				minNode = node;
			}
		}

		return minNode;
	}

	NavGraphNode UtilityAstar::SearchMyNodeToTargetNearNode(const GraphAstar& astar,
		const std::shared_ptr<GameObject>& startObject, const std::shared_ptr<GameObject>& target, 
		const int& from)
	{
		const auto& graph = astar.GetGraph();
		const auto& edges = graph.GetEdges(from);
		const Vec3 startPosition = startObject->GetComponent<Transform>()->GetPosition();

		float minRange = 100000.0f;
		NavGraphNode nearNode;
		for (auto& edge : edges) {
			int toIndex = edge.GetTo();
			NavGraphNode node = graph.GetNode(toIndex);
			auto toVec = node.GetPosition() - startPosition;
			if (toVec.length() < minRange) {
				nearNode = node;
				minRange = toVec.length();
			}
		}

		return nearNode;
	}

	NavGraphNode UtilityAstar::CalucTargetDirectNode(const GraphAstar& astar,
		const NavGraphNode& startNode,
		const Vec3& targetPos)
	{
		const auto& graph = astar.GetGraph();
		const auto& edges = graph.GetEdges(startNode.GetIndex());

		auto startNodePos = startNode.GetPosition();
		auto toTargetVec = targetPos - startNodePos;
		
		float minRad = 360.0f;
		NavGraphNode reNode;
		for (const auto& edge : edges) {
			auto toIndex = edge.GetTo();
			auto nextNode = graph.GetNode(toIndex);
			auto nextPos = nextNode.GetPosition();

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
	NavGraphNode UtilityAstar::CalucTargetEscapeDirectNode(const GraphAstar& astar,
		const NavGraphNode& startNode,
		const Vec3& targetPos)
	{
		const auto& graph = astar.GetGraph();
		const auto& edges = graph.GetEdges(startNode.GetIndex());

		auto startNodePos = startNode.GetPosition();
		auto toTargetVec = targetPos - startNodePos;

		float maxRad = 0.0f;
		NavGraphNode reNode;
		for (const auto& edge : edges) {
			int toIndex = edge.GetTo();
			NavGraphNode nextNode = graph.GetNode(toIndex);
			auto nextPos = nextNode.GetPosition();

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