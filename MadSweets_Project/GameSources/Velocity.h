
/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
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
		
		//�ō����x�̒���
		void MaxVelocityCheck();
		void MaxForceCheck();

		void Move();

	public:

		Velocity(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override;

		//�A�N�Z�b�T-----------------------------------------------------------

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

			////���݂̗͂̒����𓾂�
			//float MagnitudeSoFar = bsm::length(m_velocity);
			////�ő�l�Ƃ̍������߂�
			//float magnitudeRemaining = dist - MagnitudeSoFar;
			////����0�ȉ��i�܂�ő�l�𒴂��Ă�����j
			////�ǉ����Ȃ��Ń��^�[��
			//if (magnitudeRemaining <= 0.0f) {
			//	return;
			//}
			////�ǉ�����͂̑傫�������߂�
			//float MagnitudeToAdd = bsm::length(newForce);
			////�͂̒ǉ�
			//if (MagnitudeToAdd < magnitudeRemaining) {
			//	m_force += newForce;
			//	//m_force += (bsm::normalize(newForce) * MagnitudeToAdd);
			//}
			//else {
			//	//m_force += newForce;
			//	m_force += (bsm::normalize(newForce) * MagnitudeToAdd);
			//}

			//m_force += force / force.length();

			////���݂̗͂̒����𓾂�
			//MagnitudeSoFar = bsm::length(m_velocity);
			////�ő�l�Ƃ̍������߂�
			//magnitudeRemaining = dist - MagnitudeSoFar;
			////����0�ȉ��i�܂�ő�l�𒴂��Ă�����j
			////�ǉ����Ȃ��Ń��^�[��
			//if (magnitudeRemaining <= 0.0f) {
			//	return;
			//}
			////�ǉ�����͂̑傫�������߂�
			//MagnitudeToAdd = bsm::length(m_force);
			////�͂̒ǉ�
			//if (MagnitudeToAdd < magnitudeRemaining) {
			//	m_force += m_force;
			//	//m_force += (bsm::normalize(newForce) * MagnitudeToAdd);
			//}
			//else {
			//	//m_force += newForce;
			//	m_force += (bsm::normalize(m_force) * MagnitudeToAdd);
			//}

			MaxForceCheck();
			//MaxAdjust();  //�ő呬�x�̒���
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
		//	//���݂̗͂̒����𓾂�
		//	float MagnitudeSoFar = bsm::length(Force);
		//	//�ő�l�Ƃ̍������߂�
		//	float magnitudeRemaining = MaxForce - MagnitudeSoFar;
		//	//����0�ȉ��i�܂�ő�l�𒴂��Ă�����j
		//	//�ǉ����Ȃ��Ń��^�[��
		//	if (magnitudeRemaining <= 0.0f) {
		//		return false;
		//	}
		//	//�ǉ�����͂̑傫�������߂�
		//	float MagnitudeToAdd = bsm::length(ForceToAdd);
		//	//�͂̒ǉ�
		//	if (MagnitudeToAdd < magnitudeRemaining) {
		//		Force += ForceToAdd;
		//	}
		//	else {
		//		Force += (bsm::normalize(ForceToAdd) * MagnitudeToAdd);
		//	}
		//	//�ǉ����ꂽ�w�W��Ԃ�  
		//	return true;
		//}
	};

}

//endbasecross