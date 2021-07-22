#pragma once

#include "NavGraphNode.h"
#include "GraphAstar.h"

namespace basecross {

	class UtilityAstar
	{
	public:

		//ターゲットから一番近くのノードを検索する。
		static NavGraphNode SearchNearNode(const GraphAstar& astar, const std::shared_ptr<GameObject>& target);
		static NavGraphNode SearchNearNode(const GraphAstar& astar, const Vec3& targetPos);

		//自分のノードからターゲット方向にあるノードを検索
		static NavGraphNode CalucTargetDirectNode(const GraphAstar& astar,
			const NavGraphNode& startNode,
			const Vec3& targetPos);
	};

}