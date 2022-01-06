/*!
@file EnState_Attack.cpp
@brief EnState_Attack�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_Attack.h"
#include "DebugObject.h"

#include "TargetChase.h"
#include "BaseAttack.h"
#include "ReturnPlowlingPosition.h"
#include "EnemyRotationCtrl.h"

#include "Velocity.h"
#include "WallEvasion.h"

namespace basecross {

	void EnState_Attack::OnStart() {
		auto obj = GetOwner()->GetGameObject();
		
		auto attack = obj->GetComponent<BaseAttack>(false);

		auto velocity = GetOwner()->GetGameObject()->GetComponent<Velocity>(false);
		if (velocity) {
			velocity->Reset();
		}
		
		AddChangeComp(attack, true, false);
		AddChangeComp(obj->GetComponent<TargetChase>(false), false, false);
		AddChangeComp(obj->GetComponent<WallEvasion>(false), false, true);
		AddChangeComp(obj->GetComponent<EnemyRotationCtrl>(false), false, true);
		AddChangeComp(obj->GetComponent<Velocity>(false), false, true);

		StartChangeComps();
	}

	void EnState_Attack::OnUpdate() {
		//DebugObject::sm_wss << L"Attack";
	}

	void EnState_Attack::OnExit() {
		ExitChangeComps();
	}

}

//endbasecross