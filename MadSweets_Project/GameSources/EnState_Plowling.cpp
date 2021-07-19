/*!
@file EnState_Plowling.cpp
@brief EnState_Plowling‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_Plowling.h"
#include "ReturnPlowlingPosition.h"
#include "DebugObject.h"

#include "PlowlingMove.h"

namespace basecross {

	void EnState_Plowling::OnStart() {
		auto obj = GetOwner()->GetGameObject();
		AddChangeComp(obj->GetComponent<PlowlingMove>(false), true, false);
		AddChangeComp(obj->GetComponent<ReturnPlowlingPosition>(false), false, false);

		StartChangeComps();
	}

	void EnState_Plowling::OnUpdate() {
		
	}

	void EnState_Plowling::OnExit() {
		ExitChangeComps();
	}
}

//endbasecross