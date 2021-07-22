/*!
@file GraphEdge.cpp
@brief GraphEdge����
*/

#include "UtilityAstar.h"

namespace basecross {

	NavGraphNode UtilityAstar::SearchNearNode(const GraphAstar& astar, const std::shared_ptr<GameObject>& target) {
		auto targetPos = target->GetComponent<Transform>()->GetPosition();
		return SearchNearNode(astar, targetPos);
	}

	NavGraphNode UtilityAstar::SearchNearNode(const GraphAstar& astar, const Vec3& targetPos) {
		const auto& graph = astar.GetGraph();
		const auto& nodes = graph.GetNodes();

		float minRange = 10000.0f;
		NavGraphNode minNode;  //��ԋ������Z���m�[�h

		//�����J�n
		for (const auto& node : nodes) {
			auto pos = node.GetPosition();
			auto toNode = pos - targetPos;
			const auto& range = toNode.length();

			//��Q������������R���e�B�j���\


			//�������Z�������炱��ɂ���B
			if (range <= minRange) {
				minRange = range;
				minNode = node;
			}
		}

		return minNode;
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
}

//endbasecross