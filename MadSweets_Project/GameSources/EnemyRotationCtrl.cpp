/*!
@file EnemyRotationCtrl.cpp
@brief EnemyRotationCtrl‚È‚ÇŽÀ‘Ì
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
		//Œ»Ý‚Ì‰ñ“]‚ðŽæ“¾
		Quat nowQuat = transform->GetQuaternion();
		//Œ»Ý‚Æ–Ú•W‚ð•âŠÔ
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