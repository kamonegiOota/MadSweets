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
#include "PlowlingMove.h"

#include "I_Chase.h"
#include "EyeSearchRange.h"
#include "BaseAttack.h"

#include "DebugObject.h"

namespace basecross {

	void EnState_ProbTarget::OnStart() {
		auto obj = GetOwner()->GetGameObject();
		auto prob = obj->GetComponent<TargetProbe>(false);
		if (prob) {
			//prob->SetTarget(m_target);
			prob->StartProb();  //探索スタート
		}

		AddChangeComp(prob, true, false);
		AddChangeComp(obj->GetComponent<TargetChase>(false), false, false);
		AddChangeComp(obj->GetComponent<PlowlingMove>(false), false, false);

        StartChangeComps();
	}

	void EnState_ProbTarget::OnUpdate() {
		//DebugObject::sm_wss << L"Probe";

		auto object = GetOwner()->GetGameObject();
		auto targetManager = object->GetComponent<TargetManager>(false);
		auto eyeSearch = object->GetComponent<EyeSearchRange>(false);
		auto chase = object->GetComponent<I_Chase>(false);

		//nullCheck
		if (targetManager == nullptr || eyeSearch == nullptr || chase == nullptr) {
			return;
		}

		//視界にターゲットが存在したら、Chaseに切替
		auto target = targetManager->GetTarget();
		if (target) {
			auto attack = object->GetComponent<BaseAttack>(false);
			if (attack) {
				attack->Attack(target);
				return;
			}

			if (eyeSearch->IsInEyeRange(target)) {
				chase->StartChase();
			}
		}
	}

	void EnState_ProbTarget::OnExit() {
		auto obj = GetOwner()->GetGameObject();
		auto prob = obj->GetComponent<TargetProbe>(false);
		if (prob) {
			prob->ExitProbState();  //ノードのリムーブ
		}

		ExitChangeComps();
	}

}

//endbasecross