/*!
@file EnState_CheckSoundPos.cpp
@brief EnState_CheckSoundPos‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_CheckSoundPos.h"
#include "DebugObject.h"

#include "CheckTargetPos.h"
#include "TargetChase.h"
#include "PlowlingMove.h"
#include "ReturnPlowlingPosition.h"
#include "Velocity.h"

#include "AstarCtrl.h"
#include "I_Ear.h"

namespace basecross {

	void EnState_CheckSoundPos::OnStart() {
		auto obj = GetOwner()->GetGameObject();

		auto astar = obj->GetComponent<AstarCtrl>(false);
		if (astar) {
			astar->SearchAstarStart(m_targetPos);
		}
		
		AddChangeComp(obj->GetComponent<CheckTargetPos>(false), true, false);
		AddChangeComp(obj->GetComponent<PlowlingMove>(false), false, false);
		AddChangeComp(obj->GetComponent<ReturnPlowlingPosition>(false), false, false);

		StartChangeComps();

		DebugObject::sm_wss << L"Listen" << endl;
	}

	void EnState_CheckSoundPos::OnUpdate() {
		//DebugObject::m_wss << L"Chase";
		auto obj = GetOwner()->GetGameObject();
		auto checkTarget = obj->GetComponent<CheckTargetPos>(false);
		if (checkTarget == nullptr) {
			return;
		}

		if (checkTarget->IsRouteEnd()) {
			auto ear = obj->GetComponent<I_Ear>();
			if (ear) {
				ear->EndListen();
			}
		}
	}

	void EnState_CheckSoundPos::OnExit() {
		auto obj = GetOwner()->GetGameObject();
		auto checkTarget = obj->GetComponent<CheckTargetPos>(false);
		if (checkTarget) {
			checkTarget->SetIsRouteEnd(false);
		}

		ExitChangeComps();
	}

}

//endbasecross