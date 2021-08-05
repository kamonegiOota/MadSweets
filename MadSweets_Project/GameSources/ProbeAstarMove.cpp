/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "ProbeAstarMove.h"
#include "Velocity.h"
#include "UtilVelocity.h"
#include "EnemyRotationCtrl.h"

namespace basecross {

	void ProbeAstarMove::Rotation(const Vec3& moveVec) {
		auto rotCtrl = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
		if (rotCtrl) {
			rotCtrl->SetDirect(moveVec);
		}
	}

	void ProbeAstarMove::OnStart() {
		//Velocity���g���Ƃ��̏����l��ݒ�
		BaseUseVelocity::SetVelocityMaxSpeed(3.0f);
		BaseUseVelocity::SetArriveNearRnage(15.0f);
	}

	void ProbeAstarMove::Move() {
		auto obj = GetGameObject();
		auto astar = obj->GetComponent<AstarCtrl>(false);
		auto veloComp = obj->GetComponent<Velocity>(false);
		if (!astar || !veloComp) {
			return;
		}

		astar->UpdateVelocityMove(GetVelocityMaxSpeed(), GetArriveNearRange());
	}

	void ProbeAstarMove::CalucRoute(const std::shared_ptr<GameObject>& target) {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			astar->SearchAstarForecastStart(target);
		}
	}

}

//endbasecross