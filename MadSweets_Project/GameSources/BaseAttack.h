/*!
@file SearchObject.h
@brief SearchObject�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// <summary>
	/// �U���p�����[�^�̍\����
	/// </summary>
	struct AttackParam {
		float range = 1.0f;
		float power = 1.0f;

		AttackParam()
			:AttackParam(1.0f,1.0f)
		{}

		AttackParam(const float& range,
			const float& power
		):
			range(range),
			power(power)
		{}
	};

	class BaseAttack : public Component
	{
	protected:

		std::shared_ptr<GameObject> m_target;
		bool m_isAttack = false;
		AttackParam m_param;

		/// <summary>
		/// �^�[�Q�b�g���͈͓��ɂ��邩�ǂ������f
		/// </summary>
		/// <param name="isObstacleChek">��Q���`�F�b�N�����邩�ǂ���</param>
		/// <returns>�͈͓��Ȃ�true��Ԃ�</returns>
		virtual bool IsAttackRange(const bool isObstacleChek = true);

		virtual void ChangeAttackState() = 0;
		virtual void ChangeEndState() = 0;

	public:

		BaseAttack(const std::shared_ptr<GameObject>& objPtr)
			:BaseAttack(objPtr,AttackParam())
		{}

		BaseAttack(const std::shared_ptr<GameObject>& objPtr,
			const AttackParam& param
		):
			Component(objPtr),m_param(param)
		{}

		virtual void OnCreate() override{}
		virtual void OnUpdate() override{}

		virtual void Attack(const std::shared_ptr<GameObject>& target) = 0;

		//�A�N�Z�b�T-------------------------------------------------

		//�^�[�Q�b�g�̃Z�b�g
		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			return m_target;
		}

		//�U���͈�
		void SetRange(const float& range) {
			m_param.range = range;
		}
		float GetRange() const {
			return m_param.range;
		}
		
		//�U����
		void SetAttackPower(const float& power) {
			m_param.power = power;
		}
		float GetAttackPower() const {
			return m_param.power;
		}
	};

}

//endbasecross