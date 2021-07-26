
/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
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
		Vec3 desiredVelocity = normalize(toVec) * maxSpeed;  //希望のベクトル
		return (desiredVelocity - velocity);
	}

	Vec3 UtilVelocity::CalucArriveVec(const Vec3& velocity, const Vec3& toVec, float maxSpeed, float decl) {
		//Vec3 toTarget = toVec;
		float dist = toVec.length();
		if (dist > 0) {
			constexpr float DecelerationTweaker = 0.3f;  //減速値
			//指定された減速で目標に到達する式
			float speed = dist / (decl * DecelerationTweaker); 
			speed = maru::Mathf::Min(speed,maxSpeed);
			Vec3 desiredVelocity = toVec * speed / dist; //希望のベクトル
			//Vec3 desiredVelocity = toVec; //希望のベクトル
			auto steerVec = desiredVelocity - velocity;  //ステアリングベクトル
			//auto steerVec = toVec - velocity;  //ステアリングベクトル
			//return MaxSteerVecCheck(steerVec);  //最大値の制限
			return steerVec;
		}
		return Vec3(0, 0, 0);
	}
}

//endbasecross