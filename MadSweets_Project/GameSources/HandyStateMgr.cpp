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

	//ノート、エッジ追加----------------------------------------------------------------------------------

	void HandyStateMgr::AddNodes(const std::shared_ptr<HandyStateMachine>& state) {
		auto object = GetGameObject()->GetComponent<BaseEnemy>();

		state->AddNode(StateType::Plowling,    make_shared<EnState_Plowling>(object));
		state->AddNode(StateType::Chase,	   make_shared<EnState_TargetChase>(object, nullptr));
		state->AddNode(StateType::Probe,	   make_shared<EnState_ProbTarget>(object, nullptr));
		state->AddNode(StateType::Lose,		   make_shared<EnState_LoseTarget>(object));
		state->AddNode(StateType::Attack,      make_shared<EnState_Attack>(object, nullptr));
	}

	void HandyStateMgr::AddEdges(const std::shared_ptr<HandyStateMachine>& state) {
		//探索行動時
		state->AddEdge(StateType::Plowling, StateType::Attack,   &ToAttackTrigger);
		state->AddEdge(StateType::Plowling, StateType::Chase,    &ToChaseTrigger);
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
	}

	//Start,Update-------------------------------------------------------------------------

	void HandyStateMgr::OnStart() {
		//auto state = GetGameObject()->AddComponent<HandyStateMachine>();
		m_stateMachine = std::make_shared<HandyStateMachine>();

		AddNodes(m_stateMachine);
		AddEdges(m_stateMachine);
	}

	void HandyStateMgr::OnUpdate() {
		//auto stateMachine = GetGameObject()->GetComponent<HandyStateMachine>(false);
		//if (stateMachine) {
		//	if (stateMachine->IsEmpty()) {
		//		return;
		//	}
		//	
		//	auto node = stateMachine->GetNowNode();
		//	if (node) {
		//		node->OnUpdate();
		//	}
		//}

		m_stateMachine->OnUpdate();

		//testkey
		auto& key = App::GetApp()->GetMyInputDevice()->GetKeyBoard();

		if (key.IsInputDown(itbs::Input::KeyCode::DownArrow)) {
			//GetStage()->RemoveGameObject<GameObject>(m_testObj.GetShard());
		}

		if (key.IsInputDown(itbs::Input::KeyCode::UpArrow)) {
			
			//auto targetMgr = GetGameObject()->AddComponent<TargetMgr>();
			//auto obj = GetStage()->AddGameObject<GameObject>();
			//targetMgr->SetTarget(obj);
			//auto target = targetMgr->GetTarget();
			//if (target) {
			//	DebugObject::AddString(L"aru");
			//}
			//else {
			//	DebugObject::AddString(L"null");
			//}
			//m_testObj = obj;
			//return;

			DebugObject::AddString(L"Attack");
			//m_stateMachine->SetChangeOnceFunc(StateType::Attack,[m_stateMachine]() {
			//	//ターゲットを指定する処理
			//	auto player = maru::MyUtility::GetGameObject<PlayerObject>();
			//	auto state = stateMachine->GetNode(StateType::Attack);
			//	auto attackState = dynamic_pointer_cast<EnState_Attack>(state);
			//	attackState->SetTarget(player);
			//});
			auto& transition = m_stateMachine->GetTransitionStructMember();
			transition.attackTrigger.Fire();
		}
	}

}

//endbasecross