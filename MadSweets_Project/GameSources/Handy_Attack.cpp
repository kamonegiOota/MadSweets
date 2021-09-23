/*!
@file SearchObject.cpp
@brief SearchObject‚È‚ÇŽÀ‘Ì
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
#include "MyUtility.h"

#include "TargetMgr.h"
#include "HandyStateMgr.h"

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
		//auto targetMgr = GetGameObject()->GetComponent<TargetMgr>(false);
		//if (targetMgr) {
		//	targetMgr->SetTarget(m_target);
		//}

		//auto stateMgr = GetGameObject()->GetComponent<HandyStateMgr>(false);
		//if (stateMgr) {
		//	auto state = stateMgr->GetStateMachine();
		//	state->GetTransitionStructMember().attackTrigger.Fire();
		//}

		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy) {
			enemy->ChangeStateMachine<EnState_Attack>(m_target);
		}
	}

	void Handy_Attack::ChangeEndState() {
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy) {
			enemy->ChangeStateMachine<EnState_TargetChase>(m_target);
			SetUpdateActive(false);
		}
	}

	void Handy_Attack::ChangeAttackAnimation() {
		auto animeCtrl = GetGameObject()->GetComponent<HandyAnimatorCtrl>(false);
		if (animeCtrl) {
			auto anime = animeCtrl->GetAnimator();
			anime->GetMemberRefarence().attackTrigger.Fire();
		}	
	}

	void Handy_Attack::Rotation(const Vec3& direction) {
		transform->SetForward(direction);
	}

	void Handy_Attack::Attack(const std::shared_ptr<GameObject>& target) {
		//UŒ‚ó‘Ô‚È‚ç‘JˆÚ‚ð‚µ‚È‚¢
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy->IsEqualStateType<EnState_Attack>()) {
			return;
		}
		SetTarget(target);

		if (IsAttackRange()) {
			CreateThrowObject();
			ChangeAttackAnimation();
			ChangeAttackState();
			SetUpdateActive(true);
		}
	}

	void Handy_Attack::OnCreate() {
		SetUpdateActive(false);
	}

	void Handy_Attack::OnUpdate() {
		Rotation(maru::MyUtility::CalucToTargetVec(GetGameObject(),m_target));
	}

}

//endbasecross