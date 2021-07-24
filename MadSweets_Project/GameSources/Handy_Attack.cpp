/*!
@file SearchObject.cpp
@brief SearchObject‚È‚ÇÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "Handy_Attack.h"
#include "BaseEnemy.h"
#include "EnState_Attack.h"

#include "EnState_TargetChase.h"

#include "DebugObject.h"

namespace basecross {

	Handy_Attack::Handy_Attack(const std::shared_ptr<GameObject>& objPtr)
		:Handy_Attack(objPtr,AttackParam(5.0f,1.0f))
	{}

	Handy_Attack::Handy_Attack(const std::shared_ptr<GameObject>& objPtr,
		const AttackParam& param
	):
		BaseAttack(objPtr,param)
	{}

	void Handy_Attack::ChangeAttackState() {
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy) {
			enemy->ChangeStateMachine<EnState_Attack>(m_target);
		}
	}

	void Handy_Attack::ChangeEndState() {
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy) {
			enemy->ChangeStateMachine<EnState_TargetChase>(m_target);
		}
	}


	bool Handy_Attack::IsEnd() {
		//‚±‚±‚ÉI‚í‚éğŒ‚Ì‹Lq
		//Œ»İ‰¼ó‘Ô
		return true;
	}

	void Handy_Attack::UpdateAttack() {
		//AddAction<Handy_Attack>(GetThis<Handy_Attack>(), &Handy_Attack::ChangeEndState,5.0f);


		//‰¼‚Ìó‘Ô
		auto delta = App::GetApp()->GetElapsedTime();

		m_delay += -1.0f * delta;

		if (IsEnd() && m_delay <= 0.0f) {
			m_delay = 3.0f;
			ChangeEndState();
			m_updateFunc = nullptr;
		}
	}

	void Handy_Attack::Attack(const std::shared_ptr<GameObject>& target) {
		SetTarget(target);

		if (IsAttackRange()) {
			m_updateFunc = &Handy_Attack::UpdateAttack;
			ChangeAttackState();
		}
	}

	void Handy_Attack::OnCreate() {

	}

	void Handy_Attack::OnUpdate() {
		if (m_updateFunc) {
			m_updateFunc(*this);
		}
	}

}

//endbasecross