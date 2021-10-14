/*!
@file EnState_Plowling.cpp
@brief EnState_Plowling‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_EscapeMove.h"

#include "PlowlingMove.h"
#include "AstarPlowlingMove.h"
#include "TargetEscape.h"
#include "AstarCtrl.h"
#include "TargetMgr.h"

#include "DebugObject.h"

namespace basecross {

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
		//DebugObject::AddString(L"Escape");
	}

	void EnState_EscapeMove::OnExit() {
		ExitChangeComps();

		DebugObject::AddString(L"ExitEscape");
	}

}

//endbasecross