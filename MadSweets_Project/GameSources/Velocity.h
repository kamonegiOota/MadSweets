
/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "Mathf.h"
#include "DebugObject.h"

namespace basecross {

	class Velocity : public Component
	{
		Vec3 m_force = Vec3(0.0f);
		Vec3 m_velocity = Vec3(0.0f);
		float m_maxSpeed = 3.0f;
		float m_maxForce = 10.0f;
		
		//最高速度の調整
		void MaxVelocityCheck();
		void MaxForceCheck();

		void Move();

	public:

		Velocity(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override;

		//アクセッサ-----------------------------------------------------------

		void Reset() {
			m_force = Vec3(0.0f);
			m_velocity = Vec3(0.0f);
		}

		//void AddForce(Vec3 force) {
		//	//m_force += force;

		//	auto newDot = dot(m_force.GetNormalized(),force.GetNormalized());
		//	auto rad = acosf(newDot);

		//	//DebugObject::m_wss << to_wstring(XMConvertToDegrees(rad));
		//	//DebugObject::sm_isResetDelta = true;

		//	if (rad >= XMConvertToRadians(5.0f)) {
		//		m_force += force;
		//	}
		//	else {
		//		m_force += force;
		//	}

		//	MaxForceCheck();
		//}


		void AddForce(const Vec3& force) {
			//m_velocity += force;

			//auto dist = force.length();

			//auto speed = dist / 0.3f * 3.0f;
			//speed = maru::Mathf::Clamp(speed, 0.0f, m_maxSpeed);

			//auto newVelo = force * speed / dist;
			//auto newForce = newVelo - m_velocity;

			//m_force = newForce;

			Vec3 newForce(0.0f);
			if (force.length() <= 3.0f) {
				newForce = Arrive(m_velocity, force, m_maxSpeed, 3.0f);
			}
			else {
				newForce = Seek(m_velocity, force, m_maxSpeed);
			}

			//auto tempForce = m_force;
			//AccumulateForce(tempForce, newForce, m_maxForce);
			
			//m_force = tempForce;

			m_force = newForce;

			////現在の力の長さを得る
			//float MagnitudeSoFar = bsm::length(m_velocity);
			////最大値との差を求める
			//float magnitudeRemaining = dist - MagnitudeSoFar;
			////差が0以下（つまり最大値を超えていたら）
			////追加しないでリターン
			//if (magnitudeRemaining <= 0.0f) {
			//	return;
			//}
			////追加する力の大きさを求める
			//float MagnitudeToAdd = bsm::length(newForce);
			////力の追加
			//if (MagnitudeToAdd < magnitudeRemaining) {
			//	m_force += newForce;
			//	//m_force += (bsm::normalize(newForce) * MagnitudeToAdd);
			//}
			//else {
			//	//m_force += newForce;
			//	m_force += (bsm::normalize(newForce) * MagnitudeToAdd);
			//}

			//m_force += force / force.length();

			////現在の力の長さを得る
			//MagnitudeSoFar = bsm::length(m_velocity);
			////最大値との差を求める
			//magnitudeRemaining = dist - MagnitudeSoFar;
			////差が0以下（つまり最大値を超えていたら）
			////追加しないでリターン
			//if (magnitudeRemaining <= 0.0f) {
			//	return;
			//}
			////追加する力の大きさを求める
			//MagnitudeToAdd = bsm::length(m_force);
			////力の追加
			//if (MagnitudeToAdd < magnitudeRemaining) {
			//	m_force += m_force;
			//	//m_force += (bsm::normalize(newForce) * MagnitudeToAdd);
			//}
			//else {
			//	//m_force += newForce;
			//	m_force += (bsm::normalize(m_force) * MagnitudeToAdd);
			//}

			MaxForceCheck();
			//MaxAdjust();  //最大速度の調整
		}

		void SetVelocity(const Vec3& velocity) {
			m_velocity = velocity;
		}
		Vec3 GetVelocity() const {
			return m_velocity;
		}

		bsm::Vec3 Seek(const bsm::Vec3& Velocity, const Vec3& toVec, float MaxSpeed) {
			bsm::Vec3 DesiredVelocity
				= bsm::normalize(toVec) * MaxSpeed;
			return (DesiredVelocity - Velocity);
		}

		bsm::Vec3 Arrive(const bsm::Vec3& Velocity, const Vec3& toVec ,float MaxSpeed, float Decl) {
			bsm::Vec3 ToTarget = toVec;
			float dist = bsm::length(ToTarget);
			if (dist > 0) {
				const float DecelerationTweaker = 0.3f;
				float speed = dist / (Decl * DecelerationTweaker);
				speed = Util::Minimum(speed, MaxSpeed);
				bsm::Vec3 DesiredVelocity = ToTarget * speed / dist;
				return (DesiredVelocity - Velocity);
			}
			return bsm::Vec3(0, 0, 0);
		}

		//bool AccumulateForce(bsm::Vec3& Force, const bsm::Vec3& ForceToAdd, float MaxForce) {
		//	//現在の力の長さを得る
		//	float MagnitudeSoFar = bsm::length(Force);
		//	//最大値との差を求める
		//	float magnitudeRemaining = MaxForce - MagnitudeSoFar;
		//	//差が0以下（つまり最大値を超えていたら）
		//	//追加しないでリターン
		//	if (magnitudeRemaining <= 0.0f) {
		//		return false;
		//	}
		//	//追加する力の大きさを求める
		//	float MagnitudeToAdd = bsm::length(ForceToAdd);
		//	//力の追加
		//	if (MagnitudeToAdd < magnitudeRemaining) {
		//		Force += ForceToAdd;
		//	}
		//	else {
		//		Force += (bsm::normalize(ForceToAdd) * MagnitudeToAdd);
		//	}
		//	//追加された指標を返す  
		//	return true;
		//}
	};

}

//endbasecross