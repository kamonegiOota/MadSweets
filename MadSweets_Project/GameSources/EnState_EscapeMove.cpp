/*!
@file EnState_EscapeMove.cpp
@brief EnState_EscapeMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_EscapeMove.h"

#include "PlowlingMove.h"
#include "AstarPlowlingMove.h"
#include "TargetEscape.h"
#include "AstarCtrl.h"
#include "TargetManager.h"
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

		auto targetManager = obj->GetComponent<TargetManager>(false);
		if (targetManager) {
			m_target = targetManager->GetTarget();
		}

		auto targetEscape = obj->GetComponent<TargetEscape>(false);
		if (targetEscape) {
			targetEscape->SetTarget(m_target.GetShard());
		}

		auto astar = obj->GetComponent<AstarCtrl>(false);
		if (astar) {
			astar->SearchAstarEscapeStart(m_target.GetShard());
		}

		AddChangeComp(targetEscape, true, false);
		AddChangeComp(obj->GetComponent<PlowlingMove>(false), false, false);
		AddChangeComp(obj->GetComponent<AstarPlowlingMove>(false), false, false);

		StartChangeComps();

		DebugObject::AddString(L"StartEscape");
	}

	void EnState_EscapeMove::OnUpdate() {
		auto object = GetOwner()->GetGameObject();
		auto targetManager = object->GetComponent<TargetManager>(false);
		auto eyeSearch = object->GetComponent<EyeSearchRange>(false);

		//nullCheck
		if (targetManager == nullptr || eyeSearch == nullptr) {
			DebugObject::AddString(L"EnState_EscapeMove:: コンポーネントが足りません。");
			return;
		}

		//視界にターゲットが存在したら、Chaseに切替
		auto target = targetManager->GetTarget();
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