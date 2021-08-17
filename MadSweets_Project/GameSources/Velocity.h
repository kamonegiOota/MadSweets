
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
		float m_maxSpeed = 4.0f;
		float m_maxForce = 10.0f;
		float m_maxSteer = 3.0f;  //�������傫���قǐ��񂵂₷��
		float m_nearRange = 1.0f; //�߂��Ɣ��f����鋗��
		
		//�ō����x�̒���
		/// <summary>
		/// �ő呬�x����
		/// </summary>
		void MaxVelocityCheck();
		/// <summary>
		/// �ő�Force����
		/// </summary>
		void MaxForceCheck();
		/// <summary>
		/// ��x�ɉ��Z�����x�N�g���̍ő�l����
		/// </summary>
		Vec3 MaxSteerVecCheck(const Vec3& vec);  //��x�ɉ��Z�����ő�l�̐���

		//�x�N�g���v�Z�p�̊֐��B
		/// <summary>
		/// �^�[�Q�b�g�̕����̃x�N�g�������݂̑��x�ň������x�N�g����Ԃ��B
		/// </summary>
		/// <param name="velocity">���݂̑��x</param>
		/// <param name="toVec">�^�[�Q�b�g�����̃x�N�g��</param>
		/// <param name="maxSpeed">�ő呬�x</param>
		/// <returns>�u�^�[�Q�b�g�̕����̃x�N�g���v- �u���݂̑��x�v</returns>
		Vec3 CalucSeekVec(const Vec3& velocity, const Vec3& toVec, float maxSpeed);
		/// <summary>
		/// �����x�N�g����Ԃ�(�߂Â��Ə������Ȃ�x�N�g��)
		/// </summary>
		/// <param name="velocity">���݂̑��x</param>
		/// <param name="toVec">�^�[�Q�b�g�����̃x�N�g��</param>
		/// <param name="maxSpeed">�ő呬�x</param>
		/// <param name="decl"></param>
		/// <returns>�����x�N�g����Ԃ�(�߂Â��Ə������Ȃ�x�N�g��)��Ԃ�</returns>
		Vec3 CalucArriveVec(const Vec3& velocity, const Vec3& toVec, float maxSpeed, float decl = 3.0f);

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

		void AddForce(const Vec3& force) {
			m_force += force;
			MaxForceCheck();
		}

		void SetForce(const Vec3& force) {
			m_force = force;  //�͂̍X�V
			MaxForceCheck();     //�͂̍ő�l�`�F�b�N
		}
		Vec3 GetForce() const {
			return m_force;
		}

		//void AddVelocity(const Vec3& velocity) {
		//	m_velocity += velocity;
		//}

		void SetVelocity(const Vec3& velocity) {
			m_velocity = velocity;
		}
		Vec3 GetVelocity() const {
			return m_velocity;
		}

		void SetMaxSpeed(const float& speed) {
			m_maxSpeed = speed;
		}
		float GetMaxSpeed() const {
			return m_maxSpeed;
		}

		/// <summary>
		/// ���񂵂₷�����ς��ϐ�(Default�l��3.0f)
		/// </summary>
		/// <param name="steer">�ς��������񂵂₷��</param>
		void SetMaxSteer(const float& steer) {
			m_maxSteer = steer;
		}
		/// <summary>
		/// ���񂵂₷�����ς��ϐ�(Default�l��3.0f)
		/// </summary>
		/// <returns>���݂̐��񂵂₷��</returns>
		float GetMaxSteer() const {
			return m_maxSteer;
		}

		/// <summary>
		/// �Ώۂ���߂��Ɣ��f����鋗��
		/// </summary>
		/// <param name="range">�߂��Ɣ��f����鋗��</param>
		void SetNearRange(const float& range) {
			m_nearRange = range;
		}
		/// <summary>
		/// ���݂̑Ώۂ���߂��Ɣ��f����鋗��
		/// </summary>
		/// <returns>���݂̑Ώۂ���߂��Ɣ��f����鋗��</returns>
		float GetNearRange() const {
			return m_nearRange;
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