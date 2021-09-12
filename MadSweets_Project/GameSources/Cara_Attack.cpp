/*!
@file SearchObject.cpp
@brief SearchObject‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "Cara_Attack.h"
#include "BaseEnemy.h"
#include "EnState_Attack.h"
#include "ThrowCtrl.h"
#include "ThrowHandyObject.h"

#include "EnState_TargetChase.h"

#include "CaraObject.h"
#include "CaraAnimatorCtrl.h"
#include "BaseEnemy.h"
#include "EnemyRotationCtrl.h"
#include "MyUtility.h"

#include "DebugObject.h"
#include "I_Damaged.h"

namespace basecross {

	void Cara_Attack::ChangeAttackState() {
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy) {
			enemy->ChangeStateMachine<EnState_Attack>(m_target);
		}
	}

	void Cara_Attack::ChangeAttackAnimation() {
		auto animeCtrl = GetGameObject()->GetComponent<CaraAnimatorCtrl>(false);
		if (animeCtrl) {
			auto anime = animeCtrl->GetAnimator();
			anime->GetMemberRefarence().attackTrigger.Fire();
		}
	}

	void Cara_Attack::Rotation(const Vec3& direct) {
		auto rot = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
		if (rot) {
			rot->SetDirect(direct);
		}
	}

	void Cara_Attack::Attack(const std::shared_ptr<GameObject>& target) {
		//UŒ‚ó‘Ô‚È‚çˆ—‚ð‚µ‚È‚¢
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy->IsEqualStateType<EnState_Attack>()) {
			return;
		}
		SetTarget(target);

		if (IsAttackRange(false)) {
			SetUpdateActive(true);
			ChangeAttackAnimation();
			ChangeAttackState();
		}
	}

	void Cara_Attack::ProvideDamage() {
		auto damage = GetTarget()->GetComponent<I_Damaged>(false);
		if (damage && IsAttackRange()) {
			damage->Damage(m_param.power);
		}
	}

	void Cara_Attack::ChangeEndState() {
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy) {
			enemy->ChangeStateMachine<EnState_TargetChase>(m_target);
			SetUpdateActive(false);
		}
	}

	void Cara_Attack::OnCreate() {
		SetUpdateActive(false);
	}

	void Cara_Attack::OnUpdate() {
		transform->SetForward(maru::MyUtility::CalucToTargetVec(GetGameObject(), m_target));
	}
}

//endbasecross