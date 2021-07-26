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
#include "Velocity.h"

namespace basecross {

	void EnState_Plowling::OnStart() {
		auto obj = GetOwner()->GetGameObject();

		auto plow = obj->GetComponent<PlowlingMove>();

		auto velocity = obj->GetComponent<Velocity>(false);
		if (velocity) {
			velocity->Reset();
			auto range = plow->GetNearRange();
			auto speed = plow->GetMaxSpeed();
			velocity->SetNearRange(range);
			velocity->SetMaxSpeed(speed);
		}

		AddChangeComp(obj->GetComponent<PlowlingMove>(false), true, false);
		AddChangeComp(obj->GetComponent<ReturnPlowlingPosition>(false), false, false);

		StartChangeComps();

		obj->GetComponent<PNTStaticDraw>()->SetDiffuse(Col4(0.0f, 1.0f, 0.0f, 1.0f));
	}

	void EnState_Plowling::OnUpdate() {
		
	}

	void EnState_Plowling::OnExit() {
		ExitChangeComps();
	}
}

//endbasecross