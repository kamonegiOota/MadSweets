/*!
@file GraphNode.cpp
@brief GraphNode‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_Attack.h"
#include "DebugObject.h"

#include "TargetChase.h"
#include "BaseAttack.h"
#include "ReturnPlowlingPosition.h"

namespace basecross {

	void EnState_Attack::OnStart() {
		auto obj = GetOwner()->GetGameObject();
		
		auto attack = obj->GetComponent<BaseAttack>(false);
		//if (attack) {
		//	attack->Attack(m_target);
		//}

		//DebugObject::m_wss << L"Attack";
		
		AddChangeComp(attack, true, false);
		AddChangeComp(obj->GetComponent<TargetChase>(false), false, false);

		StartChangeComps();

		obj->GetComponent<PNTStaticDraw>()->SetDiffuse(Col4(1.0f, 1.0f, 0.0f, 1.0f));
	}

	void EnState_Attack::OnUpdate() {
		//DebugObject::m_wss << L"Chase";
	}

	void EnState_Attack::OnExit() {
		ExitChangeComps();
	}

}

//endbasecross