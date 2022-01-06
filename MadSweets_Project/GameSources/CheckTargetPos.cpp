/*!
@file CheckTargetPos.cpp
@brief CheckTargetPosなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "CheckTargetPos.h"

#include "EnemyRotationCtrl.h"
#include "Velocity.h"
#include "AstarCtrl.h"

#include "UtilVelocity.h"

#include "EnState_LoseTarget.h"

#include "I_Ear.h"

namespace basecross {

	void CheckTargetPos::ChangeStateMachine() {
		

		//ステートマシン変更時
		//auto ear = GetGameObject()->GetComponent<I_Ear>(false);
		//if (ear) {
		//	ear->EndListen();
		//}

		//auto enemy = GetGameObject()->GetComponent<BaseEnemy>();
		////将来的にはProbStateに変更
		//if (enemy) {
		//	//enemy->ChangeStateMachine<EnState_LoseTarget>();
		//}
	}

	void CheckTargetPos::Move() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			astar->UpdateVelocityMove(GetVelocityMaxSpeed(), GetArriveNearRange());

			if (astar->IsRouteEnd()) {
				SetIsRouteEnd(true);
			}
		}
	}

	void CheckTargetPos::OnCreate() {
		SetUpdateActive(false);
		//SetVelocityMaxSpeed();
		//SetNearRnage();
	}

	void CheckTargetPos::OnUpdate() {
		Move();
	}

}

//endbasecross