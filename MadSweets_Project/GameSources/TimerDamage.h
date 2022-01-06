
/*!
@file TimerDamage.h
@brief TimerDamage�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class TimerDamage : public Component
	{
		float m_time = 2.0f;
		float m_timeElapsed = 0.0f;

		float m_power = 1.0f;  //�_���[�W�̒l

		void Damage();
		void TimeMgr();

	public:

		TimerDamage(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;


		//�A�N�Z�b�T--------------------------------------------------

		void SetTime(const float& time) {
			m_time = time;
		}
		float GetTime() const {
			return m_time;
		}

		void SetPower(const float& power) {
			m_power = power;
		}
		float GetPowet() const {
			return m_power;
		}
	};

}

//endbasecross