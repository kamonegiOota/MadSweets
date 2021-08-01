/*!
@file GraphNode.cpp
@brief GraphNode‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_CheckSoundPos.h"
#include "DebugObject.h"

#include "TargetChase.h"
#include "ReturnPlowlingPosition.h"
#include "Velocity.h"

namespace basecross {

	void EnState_CheckSoundPos::OnStart() {
		auto obj = GetOwner()->GetGameObject();

		AddChangeComp(obj->GetComponent<ReturnPlowlingPosition>(), false, false);

		StartChangeComps();

		auto draw = obj->GetComponent<SmBaseDraw>(false);
		if (draw) {
			draw->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		}

	}

	void EnState_CheckSoundPos::OnUpdate() {
		//DebugObject::m_wss << L"Chase";
	}

	void EnState_CheckSoundPos::OnExit() {

		ExitChangeComps();
	}

}

//endbasecross