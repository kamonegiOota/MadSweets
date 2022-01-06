/*!
@file SearchObject.cpp
@brief SearchObjectなど実体
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

#include "ChaseEnemyStator.h"
#include "CaraStator.h"

#include "TargetManager.h"

#include "SoundHelper.h"
#include "CaraSounder.h"

namespace basecross {

	void Cara_Attack::PlayAttackSound() {
		auto sounder = GetGameObject()->GetComponent<CaraSounder>();
		sounder->AttackSound();
	}

	void Cara_Attack::ChangeAttackState() {
		//ステートマシン変更時
		auto stator = GetGameObject()->GetComponent<CaraStator>(false);
		if (stator) {
			stator->GetTransitionMember().attackTrigger.Fire();
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
		//攻撃状態なら処理をしない
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
		if (damage && IsAttackRange(false)) {
			damage->Damage(m_param.power);
			PlayAttackSound();
		}
	}

	void Cara_Attack::ChangeEndState() {
		//ステートマシン変更時
		auto stator = GetGameObject()->GetComponent<CaraStator>(false);
		if (stator) {
			stator->GetTransitionMember().chaseTrigger.Fire();
			SetUpdateActive(false);
		}
	}

	void Cara_Attack::OnCreate() {
		SetUpdateActive(false);
	}

	void Cara_Attack::OnUpdate() {
		auto targetManager = GetGameObject()->GetComponent<TargetManager>(false);
		if (targetManager) {
			auto target = targetManager->GetTarget();
			if (target) {
				transform->SetForward(maru::MyUtility::CalucToTargetVec(GetGameObject(), target));
			}
		}
	}
}

//endbasecross