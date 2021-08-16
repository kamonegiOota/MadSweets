/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "EnemyRotationCtrl.h"

namespace basecross {

	void EnemyRotationCtrl::RotationProcess() {
		//将来的にはゆっくり回転するようにする。
		auto direct = m_direct;
		direct.y = 0.0f;
		direct.normalize();
		transform->SetForward(direct);
	}

	void EnemyRotationCtrl::OnCreate() {
		m_direct = transform->GetForword();
	}

	void EnemyRotationCtrl::OnUpdate() {
		RotationProcess();
	}
}

//endbasecross