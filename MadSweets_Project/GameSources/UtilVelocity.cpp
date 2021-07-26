
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "UtilVelocity.h"

#include "Mathf.h"
#include "DebugObject.h"

//#include <directxmath.h>

namespace basecross {

	Vec3 UtilVelocity::MaxSpeedVecCheck(const Vec3 velocity, const float& maxSpeed) {
		auto speed = velocity.length();

		speed = maru::Mathf::Min(speed, maxSpeed);
		return normalize(velocity) * speed;
	}

	Vec3 UtilVelocity::CalucSeekVec(const Vec3& velocity, const Vec3& toVec, float maxSpeed) {
		Vec3 desiredVelocity = normalize(toVec) * maxSpeed;  //��]�̃x�N�g��
		return (desiredVelocity - velocity);
	}

	Vec3 UtilVelocity::CalucArriveVec(const Vec3& velocity, const Vec3& toVec, float maxSpeed, float decl) {
		//Vec3 toTarget = toVec;
		float dist = toVec.length();
		if (dist > 0) {
			constexpr float DecelerationTweaker = 0.3f;  //�����l
			//�w�肳�ꂽ�����ŖڕW�ɓ��B���鎮
			float speed = dist / (decl * DecelerationTweaker); 
			speed = maru::Mathf::Min(speed,maxSpeed);
			Vec3 desiredVelocity = toVec * speed / dist; //��]�̃x�N�g��
			//Vec3 desiredVelocity = toVec; //��]�̃x�N�g��
			auto steerVec = desiredVelocity - velocity;  //�X�e�A�����O�x�N�g��
			//auto steerVec = toVec - velocity;  //�X�e�A�����O�x�N�g��
			//return MaxSteerVecCheck(steerVec);  //�ő�l�̐���
			return steerVec;
		}
		return Vec3(0, 0, 0);
	}
}

//endbasecross