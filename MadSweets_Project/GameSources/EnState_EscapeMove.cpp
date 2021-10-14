/*!
@file EnState_Plowling.cpp
@brief EnState_Plowlingなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_EscapeMove.h"

#include "PlowlingMove.h"
#include "AstarPlowlingMove.h"
#include "TargetEscape.h"
#include "AstarCtrl.h"
#include "TargetMgr.h"
#include "EyeSearchRange.h"
#include "I_Escape.h"

#include "DebugObject.h"

namespace basecross {

	void EnState_EscapeMove::ChangeState() {
		auto object = GetOwner()->GetGameObject();

		auto escape = object->GetComponent<I_Escape>(false);
		if (escape) {
			escape->StartEscape();
		}
	}

	void EnState_EscapeMove::OnStart() {
		auto obj = GetOwner()->GetGameObject();

		auto targetMgr = obj->GetComponent<TargetMgr>(false);
		if (targetMgr) {
			m_target = targetMgr->GetTarget();
		}

		auto targetEscape = obj->GetComponent<TargetEscape>(false);
		if (targetEscape) {
			targetEscape->SetTarget(m_target);
		}

		auto astar = obj->GetComponent<AstarCtrl>(false);
		if (astar) {
			astar->SearchAstarEscapeStart(m_target);
		}

		AddChangeComp(targetEscape, true, false);
		AddChangeComp(obj->GetComponent<PlowlingMove>(false), false, false);
		AddChangeComp(obj->GetComponent<AstarPlowlingMove>(false), false, false);

		StartChangeComps();

		DebugObject::AddString(L"StartEscape");
	}

	void EnState_EscapeMove::OnUpdate() {
		auto object = GetOwner()->GetGameObject();
		auto targetMgr = object->GetComponent<TargetMgr>(false);
		auto eyeSearch = object->GetComponent<EyeSearchRange>(false);

		//nullCheck
		if (targetMgr == nullptr || eyeSearch == nullptr) {
			DebugObject::AddString(L"EnState_EscapeMove:: コンポーネントが足りません。");
			return;
		}

		//視界にターゲットが存在したら、Chaseに切替
		auto target = targetMgr->GetTarget();
		if (target) {
			if (eyeSearch->IsInEyeRange(target)) {
				ChangeState();
			}
		}

		//DebugObject::AddString(L"Escape");
	}

	void EnState_EscapeMove::OnExit() {
		ExitChangeComps();

		DebugObject::AddString(L"ExitEscape");
	}

}

//endbasecross