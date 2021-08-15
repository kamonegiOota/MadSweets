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
#include "AstarPlowlingMove.h"
#include "Velocity.h"

#include "TargetChase.h"
#include "TargetEscape.h"
#include "TargetProbe.h"

namespace basecross {

	void EnState_Plowling::OnStart() {
		auto obj = GetOwner()->GetGameObject();

		//auto plow = obj->GetComponent<PlowlingMove>();

		AddChangeComp(obj->GetComponent<PlowlingMove>(false), true, false);
		//AddChangeComp(obj->GetComponent<AstarPlowlingMove>(false), true, false);
		AddChangeComp(obj->GetComponent<ReturnPlowlingPosition>(false), false, false);

		AddChangeComp(obj->GetComponent<TargetChase>(false), false, false);
		AddChangeComp(obj->GetComponent<TargetEscape>(false), false, false);
		AddChangeComp(obj->GetComponent<TargetProbe>(false), false, false);

		StartChangeComps();

		auto draw = obj->GetComponent<BcBaseDraw>(false);
		if (draw) {
			draw->SetDiffuse(Col4(0.0f, 1.0f, 0.0f, 1.0f));
		}
	}

	void EnState_Plowling::OnUpdate() {
		//DebugObject::sm_wss << L"Plowling";
	}

	void EnState_Plowling::OnExit() {
		ExitChangeComps();
	}
}

//endbasecross