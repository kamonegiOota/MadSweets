/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
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

namespace basecross {

	void ReturnPlowlingPosition::ChangeStateMachine() {
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy) {
			enemy->ChangeStateMachine<EnState_Plowling>();
		}
	}

	void ReturnPlowlingPosition::Move() {
		m_astar->UpdateVelocityMove(GetVelocityMaxSpeed(),GetNearRange());

		if (m_astar->IsRouteEnd()) {
			ChangeStateMachine();
		}

		//return;

		//auto delta = App::GetApp()->GetElapsedTime();
		//auto selfPos = transform->GetPosition();
		//	auto nodePos = m_astar->GetCalucNodePos();

		//auto toVec = nodePos - selfPos;
		//selfPos += toVec.GetNormalized() * m_speed * delta;
		//transform->SetPosition(selfPos);

		//Rotation(toVec);

		//if (m_astar->IsRouteEnd()) {
		//	ChangeStateMachine();  //ステートの変更
		//}
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
	}

}

//endbasecross