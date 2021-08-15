/*!
@file SearchObject.cpp
@brief SearchObjectなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "Handy_Attack.h"
#include "BaseEnemy.h"
#include "EnState_Attack.h"
#include "ThrowCtrl.h"
#include "ThrowHandyObject.h"

#include "EnState_TargetChase.h"

#include "DebugObject.h"

#include "HandyObject.h"

namespace basecross {

	Handy_Attack::Handy_Attack(const std::shared_ptr<GameObject>& objPtr)
		:Handy_Attack(objPtr,AttackParam(5.0f,1.0f))
	{}

	Handy_Attack::Handy_Attack(const std::shared_ptr<GameObject>& objPtr,
		const AttackParam& param
	):
		BaseAttack(objPtr,param)
	{}


	void Handy_Attack::CreateThrowObject() {
		float speed = 10.0f;
		auto throwCtrl = GetGameObject()->GetComponent<ThrowCtrl>();
		if (throwCtrl) {
			throwCtrl->Throw<ThrowHandyObject>(GetGameObject(), transform->GetForword(), speed);
		}
	}

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

	void Handy_Attack::ChangeAttackAnimation() {
		auto anime = GetGameObject()->GetComponent<Animator<HandyAnimationMember, HandyAnimationState>>(false);
		if (anime) {
			anime->GetMemberRefarence().attackTrigger.Fire();
		}	
	}


	bool Handy_Attack::IsEnd() {
		//ここに終わる条件の記述
		//現在仮状態
		return true;
	}

	void Handy_Attack::UpdateAttack() {
		//AddAction<Handy_Attack>(GetThis<Handy_Attack>(), &Handy_Attack::ChangeEndState,5.0f);
		//アニメーションが終わったら移動のステートに戻るように調整する。
		auto anime = GetGameObject()->GetComponent<PNTBoneModelDraw>();
		if (anime) {
			if (anime->GetCurrentAnimation() != L"Handy_Attack") {
				ChangeEndState();
				m_updateFunc = nullptr;
			}
		}
	}

	void Handy_Attack::Attack(const std::shared_ptr<GameObject>& target) {
		SetTarget(target);

		if (IsAttackRange()) {
			m_updateFunc = &Handy_Attack::UpdateAttack;

			CreateThrowObject();
			ChangeAttackAnimation();
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