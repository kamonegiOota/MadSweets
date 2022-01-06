
/*!
@file Velocity.cpp
@brief Velocity�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "Velocity.h"
#include "Mathf.h"
#include "DebugObject.h"

#include "UtilVelocity.h"

//#include <directxmath.h>

namespace basecross {

	void Velocity::MaxVelocityCheck() {
		auto speed = m_velocity.length();

		speed = maru::Mathf::Min(speed,m_maxSpeed);
		m_velocity = m_velocity.GetNormalized() * speed;
	}

	void Velocity::MaxForceCheck() {
		auto speed = m_force.length();

		speed = maru::Mathf::Min(speed, m_maxForce);
		m_force = m_force.GetNormalized() * speed;
	}

	Vec3 Velocity::MaxSteerVecCheck(const Vec3& vec) {
		auto speed = vec.length();
		speed = maru::Mathf::Min(speed, m_maxSteer);

		return normalize(vec) * speed;
	}

	Vec3 Velocity::CalucSeekVec(const Vec3& velocity, const Vec3& toVec, float maxSpeed) {
		Vec3 desiredVelocity = normalize(toVec) * maxSpeed;  //��]�̃x�N�g��
		return (desiredVelocity - velocity);
	}

	Vec3 Velocity::CalucArriveVec(const Vec3& velocity, const Vec3& toVec, float maxSpeed, float decl) {
		//Vec3 toTarget = toVec;
		float dist = toVec.length();
		if (dist > 0) {
			//constexpr float DecelerationTweaker = 0.3f;  //�����l
			//float speed = dist / (decl * DecelerationTweaker);
			//speed = maru::Mathf::Clamp(speed, 0.0f ,maxSpeed);
			//speed = maru::Mathf::Min(speed,maxSpeed);
			//Vec3 desiredVelocity = toVec * speed / dist; //��]�̃x�N�g��
			//Vec3 desiredVelocity = toVec; //��]�̃x�N�g��
			//auto steerVec = desiredVelocity - velocity;  //�X�e�A�����O�x�N�g��
			auto steerVec = UtilVelocity::CalucArriveVec(velocity,toVec,maxSpeed,decl);

			//auto steerVec = toVec - velocity;  //�X�e�A�����O�x�N�g��
			return MaxSteerVecCheck(steerVec);  //�ő�l�̐���
		}
		return Vec3(0, 0, 0);
	}

	void Velocity::Move() {
		if (m_velocity == Vec3(0.0f)) {
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();

		auto pos = transform->GetPosition();
		pos += m_velocity * delta;
		transform->SetPosition(pos);

		m_force = Vec3(0.0f);
	}

	void Velocity::OnUpdate() {
		//���x�̉��Z
		auto delta = App::GetApp()->GetElapsedTime();
		m_velocity += m_force * delta;

		Move(); //�ړ�����

		MaxVelocityCheck();  //�ő呬�x�Ǘ�
	}

	//void Velocity::SetForce(const Vec3& force) {
	//	//Vec3 newForce(0.0f);
	//	//if (force.length() <= m_nearRange) {  //�������߂�������
	//	//	newForce = CalucArriveVec(m_velocity, force, m_maxSpeed); //�X�e�A�����O�x�N�g��
	//	//}
	//	//else {   //����������������
	//	//	newForce = CalucSeekVec(m_velocity, force, m_maxSpeed);  //�V�[�N�x�N�g��
	//	//}

	//	m_force = force;  //�͂̍X�V

	//	MaxForceCheck();     //�͂̍ő�l�`�F�b�N
	//}

}

//endbasecross