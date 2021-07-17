/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "ReturnPlowlingPosition.h"
#include "AstarCtrl.h"
#include "PlowlingMove.h"

namespace basecross {

	void ReturnPlowlingPosition::StartReturn() {
		auto obj = GetGameObject();
		auto astar = obj->GetComponent<AstarCtrl>(false);
		auto plowling = obj->GetComponent<PlowlingMove>(false);
		if (!astar || !plowling) {
			return;
		}

		auto targetPos = plowling->GetNowTargetPosition();
		astar->SearchAstarStart(targetPos);
	}

}

//endbasecross