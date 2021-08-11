/*!
@file GraphNode.cpp
@brief GraphNode‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_TargetChase.h"
#include "DebugObject.h"

#include "TargetChase.h"
#include "TargetEscape.h"
#include "TargetProbe.h"
#include "ReturnPlowlingPosition.h"
#include "Velocity.h"
#include "CheckTargetPos.h"

namespace basecross {

	void EnState_TargetChase::OnStart() {
		auto obj = GetOwner()->GetGameObject();
		auto chase = obj->GetComponent<TargetChase>(false);
		if (chase) {
			chase->SetTarget(m_target);
		}

		AddChangeComp(chase, true, false);
		AddChangeComp(obj->GetComponent<CheckTargetPos>(false), false, false);
		AddChangeComp(obj->GetComponent<ReturnPlowlingPosition>(false), false, false);
		//AddChangeComp(obj->GetComponent<TargetChase>(false), false, false);
		AddChangeComp(obj->GetComponent<TargetEscape>(false), false, false);
		AddChangeComp(obj->GetComponent<TargetProbe>(false), false, false);
		
		StartChangeComps();

		auto draw = obj->GetComponent<BcBaseDraw>(false);
		if (draw) {
			draw->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		}

	}

	void EnState_TargetChase::OnUpdate() {
		DebugObject::sm_wss << L"Chase";
	}

	void EnState_TargetChase::OnExit() {

		ExitChangeComps();
	}

}

//endbasecross