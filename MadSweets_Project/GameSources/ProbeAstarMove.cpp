/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
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
		//Velocityを使うときの初期値を設定
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
		
		//return;

		//auto delta = App::GetApp()->GetElapsedTime();

		//auto selfPos = transform->GetPosition();
		//auto targetPos = astar->GetCalucNodePos();

		//if (astar->IsRouteEnd()) {  //ターゲットが最後の場所にたどり着いていたら、移動の処理をしない
		//	return;
		//}

		//auto toVec = targetPos - selfPos;
		//auto velocity = veloComp->GetVelocity();
		//auto force = UtilVelocity::CalucNearArriveFarSeek(velocity, toVec, GetVelocityMaxSpeed(), GetNearRange()); //将来的に変数化
		//veloComp->SetForce(toVec);

		//Rotation(toVec);

		//LookCheck();
	}

	void ProbeAstarMove::CalucRoute(const std::shared_ptr<GameObject>& target) {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			astar->SearchAstarForecastStart(target);
		}
	}

}

//endbasecross