/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
�S���ҁF�ێR �T��
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "HandyAnimator.h"
#include "Handy_Attack.h"
#include "BaseEnemy.h"

#include "TargetProbe.h"

// ���@�ǉ��� -----------------------

#include "HandySounder.h"

// ------------------------------------
namespace basecross {

	using AnimeMember = HandyAnimationMember;
	using AnimeState = HandyAnimationState;

	void HandyAnimatorCtrl::CreateAnimator() {
		auto animator = GetGameObject()->AddComponent<HandyAnimator>();
		auto stateMachine = animator->CreateAnimationStateMchine();

		CreateWalkAnimator(stateMachine);
		CreateAttackAnimator(stateMachine);
		CreateHideSearchAnimator(stateMachine);
	}

	void HandyAnimatorCtrl::CreateWalkAnimator(const std::shared_ptr<HandyStateMachine>& stateMachine) {
		auto state = stateMachine->CreateAnimationState(HandyAnimationState::Walk, L"Handy_Walk", 30, true);

		state->AddTransition([](const AnimeMember& member) { return member.attackTrigger.Get(); }, AnimeState::Attack, false);
		state->AddTransition([](const AnimeMember& member) { return member.hideSearchTrigger.Get(); }, AnimeState::HideSearch, false);

		// ���@�ǉ��� -------------------------

		state->AddAnimationEvent(0.0f, &HandySounder::WalkSound);
		state->AddAnimationEvent(0.2f, &HandySounder::WalkSound);
		// --------------------------------------
	}

	void HandyAnimatorCtrl::CreateAttackAnimator(const std::shared_ptr<HandyStateMachine>& stateMachine) {
		auto state = stateMachine->CreateAnimationState(AnimeState::Attack, L"Handy_Attack", 60, false);

		state->AddTransition([](const AnimeMember& member) { return true; }, AnimeState::Walk, true);

		state->AddExitEvent([this] {
			auto attack = GetGameObject()->GetComponent<Handy_Attack>(false);
			if (attack) {
				attack->ChangeEndState();
			}
		});
	}

	void HandyAnimatorCtrl::CreateHideSearchAnimator(const std::shared_ptr<HandyStateMachine>& stateMachine) {
		auto state = stateMachine->CreateAnimationState(AnimeState::HideSearch, L"Handy_Search", 60, false);

		state->AddTransition([](const AnimeMember& member) { return true; }, AnimeState::Walk, true);
		
		state->AddExitEvent([this] {
			auto probe = GetGameObject()->GetComponent<TargetProbe>(false);
			if (probe) {
				probe->EndInvestigateHideAnimation();
			}
		});
	}

	void HandyAnimatorCtrl::OnStart() {
		CreateAnimator();
	}

}

//endbasecross