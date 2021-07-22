#pragma once

#include "NavGraphNode.h"
#include "GraphAstar.h"

namespace basecross {

	class UtilityAstar
	{
	public:

		//�^�[�Q�b�g�����ԋ߂��̃m�[�h����������B
		static NavGraphNode SearchNearNode(const GraphAstar& astar, const std::shared_ptr<GameObject>& target);
		static NavGraphNode SearchNearNode(const GraphAstar& astar, const Vec3& targetPos);

		//�����̃m�[�h����^�[�Q�b�g�����ɂ���m�[�h������
		static NavGraphNode CalucTargetDirectNode(const GraphAstar& astar,
			const NavGraphNode& startNode,
			const Vec3& targetPos);
	};

}