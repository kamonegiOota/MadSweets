/*!
@file CaraStator.cpp
@brief CaraStator‚ÌŽÀ‘Ì
’S“–ŽÒFŠÛŽR —TŠì
*/

#include "stdafx.h"
#include "Project.h"

#include "StatorBase.h"
#include "Trigger.h"
#include "BaseEnemy.h"
#include "EnemyMainStateMachine.h"
#include "CaraStator.h"

#include "EnState_Attack.h"
#include "EnState_Plowling.h"
#include "EnState_TargetChase.h"
#include "EnState_ProbeTarget.h"
#include "EnState_LoseTarget.h"
#include "EnState_CheckSoundPos.h"

namespace basecross {

	using StateType = CaraStateType;
	using TransitionMember = CaraStateTransitionMember;

	//‘JˆÚðŒ-------------------------------------------------------------

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

	//ƒm[ƒgAƒGƒbƒW’Ç‰Á----------------------------------------------------------------------------------

	void CaraStator::CreateNodes() {
		auto& state = m_stateMachine;
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>();

		state->AddNode(StateType::Plowling, make_shared<EnState_Plowling>(enemy));
		state->AddNode(StateType::Chase,    make_shared<EnState_TargetChase>(enemy, nullptr));
		state->AddNode(StateType::Probe,    make_shared<EnState_ProbTarget>(enemy, nullptr));
		state->AddNode(StateType::Lose,     make_shared<EnState_LoseTarget>(enemy));
		state->AddNode(StateType::Attack  , make_shared<EnState_Attack>(enemy, nullptr));
		state->AddNode(StateType::SoundCheck, make_shared<EnState_CheckSoundPos>(enemy, Vec3(0.0f)));
	}

	void CaraStator::CreateEdges() {
		auto& state = m_stateMachine;

		//’Tõs“®Žž
		state->AddEdge(StateType::Plowling, StateType::Attack, &ToAttackTrigger);
		state->AddEdge(StateType::Plowling, StateType::Chase,  &ToChaseTrigger);
		state->AddEdge(StateType::Plowling, StateType::SoundCheck, &ToSoundCheckTrigger);
		//state->AddEdge(StateType::Plowling, StateType::TargetChase,    [](const TransitionMember& member) { return member.chaseTrigger.Get(); } );

		//UŒ‚Žž
		state->AddEdge(StateType::Attack, StateType::Chase,    &ToChaseTrigger);
															   
		//ƒ^[ƒQƒbƒg’Ç]									    
		state->AddEdge(StateType::Chase, StateType::Attack,    &ToAttackTrigger);
		state->AddEdge(StateType::Chase, StateType::Probe,	   &ToProbeTrigger);
															   
		//ƒ^[ƒQƒbƒg‘{õŽž									   
		state->AddEdge(StateType::Probe, StateType::Chase,	   &ToChaseTrigger);
		state->AddEdge(StateType::Probe, StateType::Lose,	   &ToLoseTrigger);
		state->AddEdge(StateType::Probe, StateType::Attack,    &ToAttackTrigger);
															   
		//ƒ^[ƒQƒbƒg‘rŽ¸Žž									   
		state->AddEdge(StateType::Lose,  StateType::Chase,     &ToChaseTrigger);
		state->AddEdge(StateType::Lose,  StateType::Attack,    &ToAttackTrigger);
		state->AddEdge(StateType::Lose,  StateType::Plowling,  &ToPlowlingTrigger);

		//‰¹‚ÌŠm”Fó‘Ô
		state->AddEdge(StateType::SoundCheck, StateType::Lose, &ToLoseTrigger);
		state->AddEdge(StateType::SoundCheck, StateType::Chase, &ToChaseTrigger);
	}
	
	void CaraStator::OnStart() {
		m_stateMachine = std::make_shared<CaraStateMachine>();

		CreateNodes();
		CreateEdges();
	}

	void CaraStator::OnUpdate() {
		m_stateMachine->OnUpdate();
	}

}