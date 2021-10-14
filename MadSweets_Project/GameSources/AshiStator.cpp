/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "AshiStator.h"

#include "EnState_Plowling.h"
#include "EnState_EscapeMove.h"
#include "EnState_LoseTarget.h"

namespace basecross {

	using StateType = AshiStateType;
	using TransitionMember = AshiStateTransitionMember;

	//遷移条件-------------------------------------------------------------------------------------------

	bool ToEscapeTrigger(const TransitionMember& member) {
		return member.escapeTrigger.Get();
	}

	bool ToLoseTrigger(const TransitionMember& member) {
		return member.loseTrigger.Get();
	}

	bool ToPlowlingTrigger(const TransitionMember& member) {
		return member.plowlingTrigger.Get();
	}

	//ノート、エッジ追加----------------------------------------------------------------------------------

	void AshiStator::CreateNodes() {
		auto& state = m_stateMachine;
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>();

		state->AddNode(StateType::Plowling, make_shared<EnState_Plowling>(enemy));
		state->AddNode(StateType::Escape, make_shared<EnState_EscapeMove>(enemy));
		state->AddNode(StateType::Lose, make_shared<EnState_LoseTarget>(enemy));
	}

	void AshiStator::CreateEdges() {
		auto& state = m_stateMachine;

		//探索行動時
		state->AddEdge(StateType::Plowling, StateType::Escape, &ToEscapeTrigger);

		//逃げている時
		state->AddEdge(StateType::Escape, StateType::Lose, &ToLoseTrigger);

		//ターゲット喪失時
		state->AddEdge(StateType::Lose, StateType::Plowling, &ToPlowlingTrigger);
	}

	void AshiStator::OnStart() {
		m_stateMachine = make_shared<StateMachine>();

		CreateNodes();
		CreateEdges();
	}

	void AshiStator::OnUpdate() {
		if (m_stateMachine) {
			m_stateMachine->OnUpdate();
		}
	}

}

//endbasecross