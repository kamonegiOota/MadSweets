/*!
@file GraphNode.cpp
@brief GraphNode‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_ProbeTarget.h"
#include "DebugObject.h"

#include "TargetChase.h"
#include "ReturnPlowlingPosition.h"
#include "Velocity.h"

namespace basecross {

	void EnState_ProbTarget::OnStart() {
		auto obj = GetOwner()->GetGameObject();



		StartChangeComps();

		auto draw = obj->GetComponent<BcBaseDraw>(false);
		if (draw) {
			draw->SetDiffuse(Col4(1.0f, 0.0f, 1.0f, 1.0f));
		}
	}

	void EnState_ProbTarget::OnUpdate() {
		//DebugObject::m_wss << L"Chase";
	}

	void EnState_ProbTarget::OnExit() {

		ExitChangeComps();
	}

}

//endbasecross