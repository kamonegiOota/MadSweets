/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
’S“–ÒFŠÛR —TŠì
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

#include "MyUtility.h"
#include "PlayerObject.h"
#include "Handy_Attack.h"

#include "DebugObject.h"

namespace basecross {

	using StateType = HandyStateType;
	using TransitionMember = HandyStateTransitionMember;

	void HandyStateMgr::AddNodes(const std::shared_ptr<HandyStateMachine>& state) {
		auto object = GetGameObject()->GetComponent<BaseEnemy>();

		state->AddNode(StateType::Plowling,    make_shared<EnState_Plowling>(object));
		state->AddNode(StateType::TargetChase, make_shared<EnState_TargetChase>(object, nullptr));
		state->AddNode(StateType::TargetProbe, make_shared<EnState_ProbTarget>(object, nullptr));
		state->AddNode(StateType::TargetLose,  make_shared<EnState_LoseTarget>(object));
		state->AddNode(StateType::Attack,      make_shared<EnState_Attack>(object, nullptr));
	}

	void HandyStateMgr::AddEdges(const std::shared_ptr<HandyStateMachine>& state) {
		//’Tõs“®
		state->AddEdge(StateType::Plowling, StateType::Attack,         [](const TransitionMember& member) { return member.attackTrigger.Get(); } );
		state->AddEdge(StateType::Plowling, StateType::TargetChase,    [](const TransitionMember& member) { return member.chaseTrigger.Get(); } );

		//UŒ‚
		state->AddEdge(StateType::Attack, StateType::TargetChase,      [](const TransitionMember& member) { return member.chaseTrigger.Get(); });

		//ƒ^[ƒQƒbƒg’Ç]
		state->AddEdge(StateType::TargetChase, StateType::Attack,      [](const TransitionMember& member) { return member.attackTrigger.Get(); });
		state->AddEdge(StateType::TargetChase, StateType::TargetProbe, [](const TransitionMember& member) { return member.probeTrigger.Get(); });

		//ƒ^[ƒQƒbƒg‘{õ
		state->AddEdge(StateType::TargetProbe, StateType::TargetChase, [](const TransitionMember& member) { return member.chaseTrigger.Get(); });
		state->AddEdge(StateType::TargetProbe, StateType::TargetLose,  [](const TransitionMember& member) { return member.loseTrigger.Get(); });
		state->AddEdge(StateType::TargetProbe, StateType::Attack,      [](const TransitionMember& member) { return member.attackTrigger.Get(); });

		//ƒ^[ƒQƒbƒg‘r¸
		state->AddEdge(StateType::TargetLose,  StateType::TargetChase, [](const TransitionMember& member) { return member.chaseTrigger.Get(); });
		state->AddEdge(StateType::TargetLose,  StateType::Attack,      [](const TransitionMember& member) { return member.attackTrigger.Get(); });
		state->AddEdge(StateType::TargetLose,  StateType::Plowling,    [](const TransitionMember& member) { return member.plowlingTrigger.Get(); });
	}

	void HandyStateMgr::OnStart() {
		auto state = GetGameObject()->AddComponent<HandyStateMachine>();

		AddNodes(state);
		AddEdges(state);
	}

	void HandyStateMgr::OnUpdate() {
		auto stateMachine = GetGameObject()->GetComponent<HandyStateMachine>(false);
		if (stateMachine) {
			if (stateMachine->IsEmpty()) {
				return;
			}
			
			auto node = stateMachine->GetNowNode();
			if (node) {
				node->OnUpdate();
			}
		}

		//testkey
		auto& key = App::GetApp()->GetMyInputDevice()->GetKeyBoard();

		if (key.IsInputDown(itbs::Input::KeyCode::UpArrow)) {
			DebugObject::AddString(L"Attack");
			stateMachine->SetChangeOnceFunc(StateType::Attack,[stateMachine]() {
				//ƒ^[ƒQƒbƒg‚ğw’è‚·‚éˆ—
				auto player = maru::MyUtility::GetGameObject<PlayerObject>();
				auto state = stateMachine->GetNode(StateType::Attack);
				auto attackState = dynamic_pointer_cast<EnState_Attack>(state);
				attackState->SetTarget(player);
			});
			auto& transition = stateMachine->GetTransitionStructMember();
			transition.attackTrigger.Fire();
		}
	}

}

//endbasecross