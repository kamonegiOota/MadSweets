/*!
@file EnState_Plowling.cpp
@brief EnState_Plowling‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_EscapeMove.h"

#include "PlowlingMove.h"
#include "TargetEscape.h"
#include "AstarCtrl.h"

#include "DebugObject.h"

namespace basecross {

	void EnState_EscapeMove::OnStart() {
		auto obj = GetOwner()->GetGameObject();
		auto targetEscape = obj->GetComponent<TargetEscape>(false);
		if (targetEscape) {
			targetEscape->SetTarget(m_target);
		}

		auto astar = obj->GetComponent<AstarCtrl>(false);
		if (astar) {
			astar->SearchAstarEscapeStart(m_target);
		}

		AddChangeComp(targetEscape, true, false);
		AddChangeComp(astar, true, false);
		AddChangeComp(obj->GetComponent<PlowlingMove>(), false, false);

		StartChangeComps();

		obj->GetComponent<PNTStaticDraw>()->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
	}

	void EnState_EscapeMove::OnUpdate() {

	}

	void EnState_EscapeMove::OnExit() {
		ExitChangeComps();
	}

}

//endbasecross