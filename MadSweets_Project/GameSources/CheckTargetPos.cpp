/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "CheckTargetPos.h"

#include "EnemyRotationCtrl.h"
#include "Velocity.h"
#include "AstarCtrl.h"

#include "UtilVelocity.h"

#include "EnState_LoseTarget.h"

namespace basecross {

	void CheckTargetPos::ChangeStateMachine() {
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>();
		//将来的にはProbStateに変更
		if (enemy) {
			enemy->ChangeStateMachine<EnState_LoseTarget>();
		}
	}

	void CheckTargetPos::Move() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			astar->UpdateVelocityMove(GetVelocityMaxSpeed(), GetNearRange());

			if (astar->IsRouteEnd()) {
				ChangeStateMachine();
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