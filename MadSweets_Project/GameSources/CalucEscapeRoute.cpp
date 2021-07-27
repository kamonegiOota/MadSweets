/*!
@file CalucEscapeRoute.cpp
@brief CalucEscapeRouteなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "AstarCtrl.h"
#include "CalucEscapeRoute.h"
#include "UtilityAstar.h"

namespace basecross {

	NavGraphNode CalucEscapeRoute::CalucRoute(const GraphAstar& astar,
		const std::shared_ptr<GameObject>& selfObj,
		const std::shared_ptr<GameObject>& targetObj) 
	{
		auto selfPos = selfObj->GetComponent<Transform>()->GetPosition();
		auto targetPos = targetObj->GetComponent<Transform>()->GetPosition();

		return CalucRoute(astar, selfPos, targetPos);
	}

	NavGraphNode CalucEscapeRoute::CalucRoute(const GraphAstar& astar,
		const Vec3& selfPos, const Vec3& targetPos)
	{
		auto selfNode = UtilityAstar::SearchNearNode(astar,selfPos);
		auto targetNode = UtilityAstar::SearchNearNode(astar,targetPos);

		//相手から一番近いノードから自分に向かうノードを検索
		auto escapeNode = UtilityAstar::CalucTargetDirectNode(astar, targetNode, selfPos);  //一番最初に逃げる方向のノードを設定

		return escapeNode;
	}

	NavGraphNode CalucEscapeRoute::CalucNextRoute(const GraphAstar& astar,
		const std::shared_ptr<GameObject>& selfObj,
		const std::shared_ptr<GameObject>& targetObj)
	{
		auto selfPos = selfObj->GetComponent<Transform>()->GetPosition();
		auto targetPos = selfObj->GetComponent<Transform>()->GetPosition();

		return CalucNextRoute(astar, selfPos,targetPos);
	}

	NavGraphNode CalucEscapeRoute::CalucNextRoute(const GraphAstar& astar,
		const Vec3& selfPos, const Vec3& targetPos)
	{
		auto selfNode = UtilityAstar::SearchNearNode(astar, selfPos);

		//ターゲットの反対側に出るルート
		return UtilityAstar::CalucTargetEscapeDirectNode(astar, selfNode, targetPos);
	}

}

//endbasecross