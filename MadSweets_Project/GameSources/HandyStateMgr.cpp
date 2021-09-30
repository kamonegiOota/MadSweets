/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
担当者：丸山 裕喜
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "HandyStateMgr.h"

#include "EnemyMainStateMachine.h"

#include "EnState_Attack.h"
#include "EnState_Plowling.h"
#include "EnState_TargetChase.h"
#include "EnState_ProbeTarget.h"
#include "EnState_LoseTarget.h"
#include "EnState_CheckSoundPos.h"

#include "MyUtility.h"
#include "PlayerObject.h"
#include "Handy_Attack.h"

#include "DebugObject.h"
#include "TargetMgr.h"

namespace basecross {

	using StateType = HandyStateType;
	using TransitionMember = HandyStateTransitionMember;

	//遷移条件-------------------------------------------------------------

	bool ToAttackTrigger(const TransitionMember& member) {
		return member.attackTrigger.Get();
	}

	bool ToChaseTrigger(const TransitionMember& member) {
		return member.chaseTrigger.Get();
	}

	bool ToProbeTrigger(const TransitionMember& member) {
		return member.probeTrigger.Get();
	}

	bool ToLoseTrigger(const TransitionMember& member) {
		return member.loseTrigger.Get();
	}

	bool ToPlowlingTrigger(const TransitionMember& member) {
		return member.plowlingTrigger.Get();
	}

	bool ToSoundCheckTrigger(const TransitionMember& member) {
		return member.soundCheckTrigger.Get();
	}

	//ノート、エッジ追加----------------------------------------------------------------------------------

	void HandyStateMgr::AddNodes(const std::shared_ptr<HandyStateMachine>& state) {
		auto object = GetGameObject()->GetComponent<BaseEnemy>();

		state->AddNode(StateType::Plowling,    make_shared<EnState_Plowling>(object));
		state->AddNode(StateType::Chase,	   make_shared<EnState_TargetChase>(object));
		state->AddNode(StateType::Probe,	   make_shared<EnState_ProbTarget>(object));
		state->AddNode(StateType::Lose,		   make_shared<EnState_LoseTarget>(object));
		state->AddNode(StateType::Attack,      make_shared<EnState_Attack>(object));
		state->AddNode(StateType::SoundCheck,  make_shared<EnState_CheckSoundPos>(object ,Vec3(0.0f)));
	}

	void HandyStateMgr::AddEdges(const std::shared_ptr<HandyStateMachine>& state) {
		//探索行動時
		state->AddEdge(StateType::Plowling, StateType::Attack,     &ToAttackTrigger);
		state->AddEdge(StateType::Plowling, StateType::Chase,      &ToChaseTrigger);
		state->AddEdge(StateType::Plowling, StateType::SoundCheck, &ToSoundCheckTrigger);
		//state->AddEdge(StateType::Plowling, StateType::TargetChase,    [](const TransitionMember& member) { return member.chaseTrigger.Get(); } );

		//攻撃時
		state->AddEdge(StateType::Attack, StateType::Chase,      &ToChaseTrigger);

		//ターゲット追従
		state->AddEdge(StateType::Chase, StateType::Attack,      &ToAttackTrigger);
		state->AddEdge(StateType::Chase, StateType::Probe,		 &ToProbeTrigger);

		//ターゲット捜索時
		state->AddEdge(StateType::Probe, StateType::Chase,		 &ToChaseTrigger);
		state->AddEdge(StateType::Probe, StateType::Lose,		 &ToLoseTrigger);
		state->AddEdge(StateType::Probe, StateType::Attack,      &ToAttackTrigger);

		//ターゲット喪失時
		state->AddEdge(StateType::Lose,  StateType::Chase,		 &ToChaseTrigger);
		state->AddEdge(StateType::Lose,  StateType::Attack,      &ToAttackTrigger);
		state->AddEdge(StateType::Lose,  StateType::Plowling,    &ToPlowlingTrigger);

		//音の確認状態
		state->AddEdge(StateType::SoundCheck, StateType::Lose,   &ToLoseTrigger);
		state->AddEdge(StateType::SoundCheck, StateType::Chase,  &ToChaseTrigger);
	}

	//Start,Update-------------------------------------------------------------------------

	void HandyStateMgr::OnStart() {
		m_stateMachine = std::make_shared<HandyStateMachine>();

		AddNodes(m_stateMachine);
		AddEdges(m_stateMachine);
	}

	void HandyStateMgr::OnUpdate() {

		m_stateMachine->OnUpdate();

		//testkey
		auto& key = App::GetApp()->GetMyInputDevice()->GetKeyBoard();
	}

}

//endbasecross