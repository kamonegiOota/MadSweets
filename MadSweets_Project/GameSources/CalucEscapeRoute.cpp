/*!
@file CalucEscapeRoute.cpp
@brief CalucEscapeRoute‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "AstarCtrl.h"
#include "CalucEscapeRoute.h"
#include "UtilityAstar.h"

namespace basecross {

	void CalucEscapeRoute::CalucRoute(const GraphAstar& astar,
		const std::shared_ptr<GameObject>& selfObj,
		const std::shared_ptr<GameObject>& targetObj) 
	{
		auto selfPos = selfObj->GetComponent<Transform>()->GetPosition();
		auto targetPos = targetObj->GetComponent<Transform>()->GetPosition();

		CalucRoute(astar, selfPos, targetPos);
	}

	void CalucEscapeRoute::CalucRoute(const GraphAstar& astar,
		const Vec3& selfPos, const Vec3& targetPos)
	{
		//auto selfNode = astar.SearchNearNode(selfPos);
		//auto targetNode = astar.SearchNearNode(targetPos);

		
	}

}

//endbasecross