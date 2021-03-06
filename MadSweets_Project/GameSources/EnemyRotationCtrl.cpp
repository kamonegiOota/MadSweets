/*!
@file EnemyRotationCtrl.cpp
@brief EnemyRotationCtrlなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "EnemyRotationCtrl.h"

namespace basecross {
	
	Quat EnemyRotationCtrl::CalcuRotationQuat(Vec3 direct, const float& speed) {
		direct.normalize();
		float angle = atan2(direct.x, direct.z);
		Quat quat;
		quat.rotationRollPitchYawFromVector(Vec3(0, angle, 0));
		quat.normalize();
		//現在の回転を取得
		Quat nowQuat = transform->GetQuaternion();
		//現在と目標を補間
		if (speed >= 1.0f) {
			return quat;
		}
		else {
			return (Quat)XMQuaternionSlerp(nowQuat, quat, speed);
		}
	}

	void EnemyRotationCtrl::RotationProcess() {
		m_direct.y = 0.0f;
		auto obj = GetGameObject();
		if (m_direct.length() > 0.0f) {
			auto quat = CalcuRotationQuat(m_direct, m_speed);
			transform->SetWorldQuaternion(quat);
		}
	}

	void EnemyRotationCtrl::OnCreate() {
		m_direct = transform->GetForword();
	}

	void EnemyRotationCtrl::OnUpdate() {
		RotationProcess();
	}
}

//endbasecross