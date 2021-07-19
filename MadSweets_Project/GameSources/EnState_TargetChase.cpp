/*!
@file GraphNode.cpp
@brief GraphNode‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_TargetChase.h"
#include "DebugObject.h"

#include "TargetChase.h"

namespace basecross {

	void EnState_TargetChase::OnStart() {
		auto obj = GetOwner()->GetGameObject();
		auto chase = obj->GetComponent<TargetChase>(false);
		if (chase) {
			chase->SetTarget(m_target);
		}

		AddChangeComp(chase, true, false);
		
		StartChangeComps();
	}

	void EnState_TargetChase::OnUpdate() {
		//DebugObject::m_wss << L"Chase";
	}

	void EnState_TargetChase::OnExit() {
		ExitChangeComps();
	}

}

//endbasecross