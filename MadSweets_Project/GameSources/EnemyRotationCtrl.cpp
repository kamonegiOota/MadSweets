/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "EnemyRotationCtrl.h"

namespace basecross {

	void EnemyRotationCtrl::RotationProcess() {
		//�����I�ɂ͂�������]����悤�ɂ���B
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