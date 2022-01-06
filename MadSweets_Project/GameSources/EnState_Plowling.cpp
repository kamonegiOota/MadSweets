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
#include "I_Escape.h"

namespace basecross {

	void EnState_Plowling::ChangeState() {
		auto object = GetOwner()->GetGameObject();

		auto chase = object->GetComponent<I_Chase>(false);
		if (chase) {
			chase->StartChase();
		}

		auto escape = object->GetComponent<I_Escape>(false);
		if (escape) {
			escape->StartEscape();
		}
	}

	void EnState_Plowling::OnStart() {
		auto obj = GetOwner()->GetGameObject();

		AddChangeComp(obj->GetComponent<PlowlingMove>(false), true, false);
		AddChangeComp(obj->GetComponent<ReturnPlowlingPosition>(false), false, false);

		AddChangeComp(obj->GetComponent<TargetChase>(false), false, false);
		AddChangeComp(obj->GetComponent<TargetEscape>(false), false, false);
		AddChangeComp(obj->GetComponent<TargetProbe>(false), false, false);

		StartChangeComps();
	}

	void EnState_Plowling::OnUpdate() {
		auto object = GetOwner()->GetGameObject();
		auto targetManager = object->GetComponent<TargetManager>(false);
		auto eyeSearch = object->GetComponent<EyeSearchRange>(false);

		//nullCheck
		if (targetManager == nullptr || eyeSearch == nullptr) {
			DebugObject::AddString(L"EnState_Plowling:: コンポーネントが足りません。");
			return;
		}

		//視界にターゲットが存在したら、Chaseに切替
		auto target = targetManager->GetTarget();
		if (target) {
			if (eyeSearch->IsInEyeRange(target)) {
				ChangeState();
			}
		}

		//DebugObject::sm_wss << L"Plowling";
	}

	void EnState_Plowling::OnExit() {
		ExitChangeComps();
	}
}

//endbasecross