/*!
@file CaraAnimatorCtrl.h
@brief CaraAnimatorCtrl
’S“–ŽÒFŠÛŽR —TŠì
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "CaraAnimatorCtrl.h"
#include "BaseEnemy.h"

#include "TargetProbe.h"
#include "Cara_Attack.h"
#include "Velocity.h"

// ”Â‹´@’Ç‰Á•ª -----------------------

//#include "HandySounder.h"

// ------------------------------------

namespace basecross {

	using AnimeMember = CaraAnimationMember;
	using AnimeState = CaraAnimationState;

	void CaraAnimatorCtrl::OnStart() {
		auto animator = GetGameObject()->AddComponent<CaraAnimator>();
		auto stateMachine = animator->CreateAnimationStateMchine();

		CreateWalkAnimator(stateMachine);
		CreateAttackAnimator(stateMachine);
		CreateHideSearchAnimator(stateMachine);
	}

	void CaraAnimatorCtrl::CreateWalkAnimator(const std::shared_ptr<CaraStateMachine>& stateMachine) {
		auto state = stateMachine->CreateAnimationState(CaraAnimationState::Walk, L"Cara_Walk", 30, true);

		state->AddTransition([](const AnimeMember& member) { return member.attackTrigger.Get(); }, AnimeState::Attack, false);
		state->AddTransition([](const AnimeMember& member) { return member.hideSearchTrigger.Get(); }, AnimeState::HideSearch, false);
	}

	void CaraAnimatorCtrl::CreateAttackAnimator(const std::shared_ptr<CaraStateMachine>& stateMachine) {
		auto state = stateMachine->CreateAnimationState(AnimeState::Attack, L"Cara_Attack", 30, false);

		state->AddTransition([](const AnimeMember& member) { return true; }, AnimeState::Walk, true);

		state->AddExitEvent([this] {
			auto attack = GetGameObject()->GetComponent<Cara_Attack>(false);
			if (attack) {
				attack->ChangeEndState();
			}
		});

		//UŒ‚”»’è
		float frameTime = 0.25f;
		state->AddAnimationEvent(frameTime, &Cara_Attack::ProvideDamage);
	}

	void CaraAnimatorCtrl::CreateHideSearchAnimator(const std::shared_ptr<CaraStateMachine>& stateMachine) {
		auto state = stateMachine->CreateAnimationState(AnimeState::HideSearch, L"Cara_Walk", 60, false);

		state->AddTransition([](const AnimeMember& member) { return true; }, AnimeState::Walk, true);

		state->AddEntryEvent([this] {
			auto velocity = GetGameObject()->GetComponent<Velocity>(false);
			if (velocity) {
				velocity->SetUpdateActive(false);
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
	}

}

//endbasecross