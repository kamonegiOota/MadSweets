/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_ProbeTarget.h"
#include "DebugObject.h"

#include "TargetChase.h"
#include "ReturnPlowlingPosition.h"
#include "Velocity.h"
#include "TargetProbe.h"

namespace basecross {

	void EnState_ProbTarget::OnStart() {
		auto obj = GetOwner()->GetGameObject();
		auto prob = obj->GetComponent<TargetProbe>(false);
		if (prob) {
			prob->SetTarget(m_target);
			prob->StartProb();  //探索スタート
		}

		AddChangeComp(obj->GetComponent<TargetProbe>(false), true, false);
		AddChangeComp(obj->GetComponent<TargetChase>(false), false, false);

		StartChangeComps();

		auto draw = obj->GetComponent<BcBaseDraw>(false);
		if (draw) {
			draw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		DebugObject::m_wss << L"Probe";
	}

	void EnState_ProbTarget::OnUpdate() {
		//DebugObject::m_wss << L"Chase";
	}

	void EnState_ProbTarget::OnExit() {

		ExitChangeComps();
	}

}

//endbasecross