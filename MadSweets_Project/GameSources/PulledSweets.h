
/*!
@file PulledSweets.h
@brief PulledSweets�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "EatenComponent.h"

namespace basecross {

	/// <summary>
	/// �X�E�B�[�c�Ɉ��������鏈��
	/// </summary>
	class PulledSweets : public Component
	{
		float m_speed;  //�z���񂹂���X�s�[�h
		float m_range;  //�z���񂹂���͈�

		/// <summary>
		/// �񂹂���������v�Z���ĕԂ�
		/// </summary>
		/// <returns>�z���񂹂������</returns>
		Vec3 CalucPulledVec();
		void PulledMove();

	public:

		PulledSweets(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr),m_speed(1.5f),m_range(10.0f)
		{}

		void OnCreate() override;
		void OnStart() override;
		void OnUpdate() override;

		//�A�N�Z�b�T--------------------------------------------------

		void SetSpeed(const float& speed) {
			m_speed = speed;
		}
		float GetSpeed() const {
			return m_speed;
		}

		void SetRange(const float& range) {
			m_range = range;
		}
		float GetRange() const {
			return m_range;
		}
	};

}

//endbasecross