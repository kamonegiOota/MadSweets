/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "ReturnPlowlingPosition.h"
#include "AstarCtrl.h"
#include "PlowlingMove.h"
#include "BaseEnemy.h"
#include "EnState_Plowling.h"
#include "EnemyRotationCtrl.h"
#include "Velocity.h"

#include "I_ReturnPlowling.h"

namespace basecross {

	void ReturnPlowlingPosition::ChangeStateMachine() {
		m_isRouteEnd = true;

		auto returnPlowling = GetGameObject()->GetComponent<I_ReturnPlowling>(false);
		if (returnPlowling) {
			returnPlowling->EndReturnPlowling();
			//enemy->ChangeStateMachine<EnState_Plowling>();
		}
	}

	void ReturnPlowlingPosition::Move() {
		m_astar->UpdateVelocityMove(GetVelocityMaxSpeed(),GetArriveNearRange());

		if (m_astar->IsRouteEnd()) {
			ChangeStateMachine();
		}
	}

	void ReturnPlowlingPosition::Rotation(const Vec3& moveVec) {
		auto rotCtrl = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
		if (rotCtrl) {
			rotCtrl->SetDirect(moveVec);
		}
	}

	void ReturnPlowlingPosition::OnCreate() {
		m_astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		SetUpdateActive(false);
	}

	void ReturnPlowlingPosition::OnUpdate() {
		if (m_astar) {
			Move();
		}
	}

	void ReturnPlowlingPosition::StartReturn() {
		auto obj = GetGameObject();
		m_astar = obj->GetComponent<AstarCtrl>(false);
		auto plowling = obj->GetComponent<PlowlingMove>(false);
		if (!m_astar || !plowling) {
			return;
		}

		auto targetPos = plowling->GetNowTargetPosition();

		m_astar->SearchAstarStart(targetPos);

		SetUpdateActive(true);

		m_isRouteEnd = false;
	}

}

//endbasecross