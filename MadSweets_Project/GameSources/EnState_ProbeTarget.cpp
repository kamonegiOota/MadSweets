/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_ProbeTarget.h"
#include "DebugObject.h"

#include "TargetChase.h"
#include "ReturnPlowlingPosition.h"
#include "Velocity.h"
#include "TargetProbe.h"
#include "PlowlingMove.h"

namespace basecross {

	void EnState_ProbTarget::OnStart() {
		auto obj = GetOwner()->GetGameObject();
		auto prob = obj->GetComponent<TargetProbe>(false);
		if (prob) {
			prob->SetTarget(m_target);
			prob->StartProb();  //�T���X�^�[�g
		}

		AddChangeComp(prob, true, false);
		AddChangeComp(obj->GetComponent<TargetChase>(false), false, false);
		AddChangeComp(obj->GetComponent<PlowlingMove>(false), false, false);

		StartChangeComps();

		DebugObject::sm_wss << L"Probe";
	}

	void EnState_ProbTarget::OnUpdate() {
		//DebugObject::m_wss << L"Chase";
		//DebugObject::sm_wss << L"Probe";
	}

	void EnState_ProbTarget::OnExit() {
		auto obj = GetOwner()->GetGameObject();
		auto prob = obj->GetComponent<TargetProbe>(false);
		if (prob) {
			prob->ExitProbState();  //�m�[�h�̃����[�u
		}

		ExitChangeComps();
	}

}

//endbasecross