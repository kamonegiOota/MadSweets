/*!
@file HandyAnimatorCtrl.h
@brief HandyAnimatorCtrl
担当者：丸山 裕喜
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "HandyAnimator.h"
#include "Handy_Attack.h"
#include "BaseEnemy.h"

#include "TargetProbe.h"
#include "Velocity.h"
#include "WallEvasion.h"

#include "HandySounder.h"

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

	//歩きモーション
	void HandyAnimatorCtrl::CreateWalkAnimator(const std::shared_ptr<HandyStateMachine>& stateMachine) {
		auto state = stateMachine->CreateAnimationState(HandyAnimationState::Walk, L"Handy_Walk", 10, true);

		state->AddTransition([](const AnimeMember& member) { return member.attackTrigger.Get(); }, AnimeState::Attack, false);
		state->AddTransition([](const AnimeMember& member) { return member.hideSearchTrigger.Get(); }, AnimeState::HideSearch, false);

		state->AddAnimationEvent(0.0f, &HandySounder::WalkSound);
		state->AddAnimationEvent(0.125f, &HandySounder::WalkSound);
	}

	//アタックモーション
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

	//隠れている場所を探す処理をする処理
	void HandyAnimatorCtrl::CreateHideSearchAnimator(const std::shared_ptr<HandyStateMachine>& stateMachine) {
		auto state = stateMachine->CreateAnimationState(AnimeState::HideSearch, L"Handy_Search", 60, false);

		state->AddTransition([](const AnimeMember& member) { return true; }, AnimeState::Walk, true);
		
		state->AddEntryEvent([this] {
			auto velocity = GetGameObject()->GetComponent<Velocity>(false);
			if (velocity) {
				velocity->SetUpdateActive(false);
			}
		});

		state->AddEntryEvent([this] {
			auto evasion = GetGameObject()->GetComponent<WallEvasion>(false);
			if (evasion) {
				evasion->SetUpdateActive(false);
			}
		});

		state->AddExitEvent([this] {
			auto probe = GetGameObject()->GetComponent<TargetProbe>(false);
			if (probe) {
				probe->EndInvestigateHideAnimation();
			}
		});
		state->AddExitEvent([this] {
			auto velocity = GetGameObject()->GetComponent<Velocity>(false);
			if (velocity) {
				velocity->SetUpdateActive(true);
			}
		});
		state->AddExitEvent([this] {
			auto evasion = GetGameObject()->GetComponent<WallEvasion>(false);
			if (evasion) {
				evasion->SetUpdateActive(true);
			}
		});
	}

	void HandyAnimatorCtrl::OnStart() {
		CreateAnimator();
	}

}

//endbasecross