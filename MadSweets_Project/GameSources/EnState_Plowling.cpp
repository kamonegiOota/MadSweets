/*!
@file EnState_Plowling.cpp
@brief EnState_Plowlingなど実体
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

#include "EyeSearchRange.h"
#include "I_Chase.h"

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
	}

	void EnState_Plowling::OnUpdate() {
		auto object = GetOwner()->GetGameObject();
		auto targetMgr = object->GetComponent<TargetMgr>(false);
		auto eyeSearch = object->GetComponent<EyeSearchRange>(false);
		auto chase = object->GetComponent<I_Chase>(false);

		//nullCheck
		if (targetMgr == nullptr || eyeSearch == nullptr || chase == nullptr) {  
			return;
		}

		//視界にターゲットが存在したら、Chaseに切替
		auto target = targetMgr->GetTarget();
		if (target) {
			if (eyeSearch->IsInEyeRange(target)) {
				chase->StartChase(target);
			}
		}

		//DebugObject::sm_wss << L"Plowling";
	}

	void EnState_Plowling::OnExit() {
		ExitChangeComps();
	}
}

//endbasecross