/*!
@file Cara_Attack.h
@brief Cara_Attack�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "BaseAttack.h"

namespace basecross {

	class Cara_Attack : public BaseAttack
	{
		void PlayAttackSound();

		void ChangeAttackState() override;
		void ChangeAttackAnimation();
		void Rotation(const Vec3& direct);

	public:
		Cara_Attack(const std::shared_ptr<GameObject>& objPtr)
			:BaseAttack(objPtr, AttackParam(1.5f,1.0f))
		{}

		Cara_Attack(const std::shared_ptr<GameObject>& objPtr,
			const AttackParam& param
		):
			BaseAttack(objPtr,param)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void Attack(const std::shared_ptr<GameObject>& target) override;
		//�X�e�[�g�I�����̏���
		void ChangeEndState() override;  

		/// <summary>
		/// �͈͓��̓G�Ƀ_���[�W��^���鏈��
		/// </summary>
		void ProvideDamage();

	};

}

//endbasecross