
/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Velocity : public Component
	{
		float m_speed = 1.0f;
		Vec3 m_direct = Vec3(0.0f);
		float m_maxSpeed = 10.0f;

		void Move();

	public:

		Velocity(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override;


		//アクセッサ-----------------------------------------------------------

		void SetSpeed(const float& speed) {
			m_speed = speed;
			m_speed = std::fmaxf(m_speed, m_maxSpeed);
		}
		float GetSpeed() const {
			return m_speed;
		}

		void SetDirect(const Vec3& direct) {
			m_direct = direct;
			m_direct.normalize();
		}
		Vec3 GetDirect() const {
			return m_direct;
		}

		void AddForce(Vec3 direct, const float& speed) {
			m_direct += direct.GetNormalized();
			m_direct.normalize();

			m_speed += speed;
			m_speed = std::fmaxf(m_speed, m_maxSpeed);
		}

		void AddForce(Vec3 force) {
			m_direct += force;
			m_direct.GetNormalized();

			m_speed += force.length();
			SetSpeed(m_speed);
		}

		Vec3 GetVelocity() const {
			return m_direct * m_speed;
		}
		void SetVelocity(const Vec3& velocity) {
			SetDirect(velocity);
			SetSpeed(velocity.length());
		}
	};

}

//endbasecross