/*!
@file SearchObject.h
@brief SearchObjectÇ»Ç«
íSìñé“ÅFä€éR óTäÏ
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "BaseAttack.h"

namespace basecross {

	class Handy_Attack : public BaseAttack
	{
		std::function<void(Handy_Attack&)> m_updateFunc = nullptr;

		float m_delay = 1.0f;

		void ChangeAttackState() override;
		void ChangeEndState() override;

		bool IsEnd();
		void UpdateAttack();

	public:
		Handy_Attack(const std::shared_ptr<GameObject>& objPtr);

		Handy_Attack(const std::shared_ptr<GameObject>& objPtr,
			const AttackParam& param);

		void OnCreate() override;
		void OnUpdate() override;

		void Attack(const std::shared_ptr<GameObject>& target) override;
	};

}

//endbasecross