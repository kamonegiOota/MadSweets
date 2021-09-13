/*!
@file GraphEdge.cpp
@brief GraphEdge����
*/

#include "UtilityAstar.h"
#include "MyUtility.h"

#include "PlayerObject.h"
#include "BaseEnemy.h"
#include "HiddenComponent.h"

namespace basecross {

	NavGraphNode UtilityAstar::SearchNearNode(const std::shared_ptr<GraphAstar>& astar, const std::shared_ptr<GameObject>& target) {
		vector<std::shared_ptr<GameObject>> excluteObjs;
		excluteObjs.push_back(target);

		auto targetPos = target->GetComponent<Transform>()->GetPosition();
		return SearchNearNode(astar, targetPos, excluteObjs);
	}

	NavGraphNode UtilityAstar::SearchNearNode(const std::shared_ptr<GraphAstar>& astar, const Vec3& targetPos,
		vector<std::shared_ptr<GameObject>> excluteObjs)
	{
		const auto& graph = astar->GetGraph();
		const auto& nodes = graph->GetNodes();

		float minRange = 10000.0f;
		NavGraphNode minNode;  //��ԋ������Z���m�[�h


		//��Q���̑ΏۊO��I��
		MyUtility::AddComponents<BaseEnemy>(excluteObjs);
		MyUtility::AddObjects<PlayerObject>(excluteObjs);
		
		//�����J�n
		for (const auto& node : nodes) {
			auto pos = node.GetPosition();
			auto toNode = pos - targetPos;
			const auto& range = toNode.length();

			//��Q������������R���e�B�j���\
			if (maru::MyUtility::IsRayObstacle(targetPos, pos, excluteObjs)) {
				continue;
			}

			//�������Z�������炱��ɂ���B
			if (range <= minRange) {
				minRange = range;
				minNode = node;
			}
		}

		return minNode;
	}

	NavGraphNode UtilityAstar::SearchMyNodeToTargetNearNode(const std::shared_ptr<GraphAstar>& astar,
		const std::shared_ptr<GameObject>& selfObject, const std::shared_ptr<GameObject>& target)
	{
		//�������g�̋߂��̃m�[�h�̌���
		const NavGraphNode selfNode = SearchNearNode(astar, selfObject);
		const int from = selfNode.GetIndex();  //���̃C���f�N�X�̎擾

		const auto& graph = astar->GetGraph();
		const auto& edges = graph->GetEdges(from);
		const Vec3 targetPosition = target->GetComponent<Transform>()->GetPosition();

		float minRange = 100000.0f;
		NavGraphNode nearNode;
		for (auto& edge : edges) {
			int toIndex = edge.GetTo();
			NavGraphNode toNode = graph->GetNode(toIndex);
			auto toVec = toNode.GetPosition() - targetPosition;
			if (toVec.length() < minRange) {
				nearNode = toNode;
				minRange = toVec.length();
			}
		}

		return nearNode;
	}

	NavGraphNode UtilityAstar::CalucTargetDirectNode(const std::shared_ptr<GraphAstar>& astar,
		const NavGraphNode& startNode,
		const Vec3& targetPos)
	{
		const auto& graph = astar->GetGraph();
		const auto& edges = graph->GetEdges(startNode.GetIndex());

		auto startNodePos = startNode.GetPosition();
		auto toTargetVec = targetPos - startNodePos;
		
		float minRad = 360.0f;
		NavGraphNode reNode;
		for (const auto& edge : edges) {
			auto toIndex = edge.GetTo();
			auto nextNode = graph->GetNode(toIndex);
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

	//�����邽�߂̃m�[�h�̌���
	NavGraphNode UtilityAstar::CalucTargetEscapeDirectNode(const std::shared_ptr<GraphAstar>& astar,
		const NavGraphNode& startNode,
		const Vec3& targetPos)
	{
		const auto& graph = astar->GetGraph();
		const auto& edges = graph->GetEdges(startNode.GetIndex());

		auto startNodePos = startNode.GetPosition();
		auto toTargetVec = targetPos - startNodePos;

		float maxRad = 0.0f;
		NavGraphNode reNode;
		for (const auto& edge : edges) {
			int toIndex = edge.GetTo();
			NavGraphNode nextNode = graph->GetNode(toIndex);
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