/*!
@file AshiAnimatorCtrl.h
@brief AshiAnimatorCtrl
�S���ҁF�ێR �T��
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "AshiAnimatorCtrl.h"
#include "BaseEnemy.h"

#include "TargetProbe.h"
//#include "Cara_Attack.h"

// ���@�ǉ��� -----------------------

//#include "HandySounder.h"

// ------------------------------------

namespace basecross {

	using AnimeMember = AshiAnimationMember;
	using AnimeState = AshiAnimationState;

	void AshiAnimatorCtrl::OnStart() {
		auto animator = GetGameObject()->AddComponent<AshiAnimator>();
		auto stateMachine = animator->CreateAnimationStateMchine();

		CreateWalkAnimator(stateMachine);
		CreateDashAnimator(stateMachine);
	}

	void AshiAnimatorCtrl::CreateWalkAnimator(const std::shared_ptr<AshiStateMachine>& stateMachine) {
		auto state = stateMachine->CreateAnimationState(AshiAnimationState::Walk, L"Ashi_Walk", 30, true);



		// ���@�ǉ��� -------------------------

		//state->AddAnimationEvent(0.0f, &HandySounder::WalkSound);
		//state->AddAnimationEvent(0.2f, &HandySounder::WalkSound);
		// --------------------------------------
	}

	void AshiAnimatorCtrl::CreateDashAnimator(const std::shared_ptr<AshiStateMachine>& stateMachine) {

	}

}

//endbasecross