/*!
@file SearchObject.cpp
@brief SearchObjectÇ»Ç«é¿ëÃ
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
#include "HandyAnimator.h"
#include "BaseEnemy.h"

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


	bool Handy_Attack::IsNowAnimeStateAttack() {
		auto animeCtrl = GetGameObject()->GetComponent<HandyAnimatorCtrl>(false);
		if (animeCtrl) {
			auto anime = animeCtrl->GetAnimator();
			//DebugObject::sm_wss << to_wstring((int)anime->GetNowState());
			//DebugObject::sm_isResetDelta = true;
			//DebugObject::AddFloat(anime->GetStateRateOfTime());
			if (anime->GetNowState() == HandyAnimationState::Attack) {
				return true;
			}
		}

		return false;
	}

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
		auto animeCtrl = GetGameObject()->GetComponent<HandyAnimatorCtrl>(false);
		if (animeCtrl) {
			auto anime = animeCtrl->GetAnimator();
			anime->GetMemberRefarence().attackTrigger.Fire();
		}	
	}

	//void Handy_Attack::UpdateAttack() {
	//	if (!IsNowAnimeStateAttack()) {  //çUåÇèÛë‘Ç≈Ç»Ç©Ç¡ÇΩÇÁ
	//		//ChangeEndState();
	//		//m_updateFunc = nullptr;
	//	}
	//}

	void Handy_Attack::Attack(const std::shared_ptr<GameObject>& target) {
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy->IsEqualStateType<EnState_Attack>()) {
			return;
		}

		SetTarget(target);

		if (IsAttackRange()) {
			CreateThrowObject();
			ChangeAttackAnimation();
			ChangeAttackState();

			//m_updateFunc = &Handy_Attack::UpdateAttack;
		}
	}

	void Handy_Attack::OnCreate() {

	}

	void Handy_Attack::OnUpdate() {
		//if (m_updateFunc) {
		//	m_updateFunc(*this);
		//}
	}

}

//endbasecross