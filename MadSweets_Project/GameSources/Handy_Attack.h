/*!
@file Handy_Attack.h
@brief Handy_Attack�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "BaseAttack.h"

namespace basecross {

	class Handy_Attack : public BaseAttack
	{
		float m_delay = 1.0f;

		bool IsNowAnimeStateAttack();  //���ݍU������������

		void StartAttack();

		void CreateThrowObject();  //������w�𐶐�

		void ChangeAttackState() override;
		void ChangeAttackAnimation();

		void Rotation(const Vec3& direction);
		

	public:
		Handy_Attack(const std::shared_ptr<GameObject>& objPtr);

		Handy_Attack(const std::shared_ptr<GameObject>& objPtr,
			const AttackParam& param);

		void OnCreate() override;
		void OnUpdate() override;

		void Attack(const std::shared_ptr<GameObject>& target) override;
		void ChangeEndState() override;  //�X�e�[�g�I�����ɂ�鏈��
	};

}

//endbasecross