/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
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

	//�J�ڏ���-------------------------------------------------------------------------------------------

	bool ToEscapeTrigger(const TransitionMember& member) {
		return member.escapeTrigger.Get();
	}

	bool ToLoseTrigger(const TransitionMember& member) {
		return member.loseTrigger.Get();
	}

	bool ToPlowlingTrigger(const TransitionMember& member) {
		return member.plowlingTrigger.Get();
	}

	//�m�[�g�A�G�b�W�ǉ�----------------------------------------------------------------------------------

	void AshiStator::CreateNodes() {
		auto& state = m_stateMachine;
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>();

		state->AddNode(StateType::Plowling, make_shared<EnState_Plowling>(enemy));
		state->AddNode(StateType::Escape, make_shared<EnState_EscapeMove>(enemy));
		state->AddNode(StateType::Lose, make_shared<EnState_LoseTarget>(enemy));
	}

	void AshiStator::CreateEdges() {
		auto& state = m_stateMachine;

		//�T���s����
		state->AddEdge(StateType::Plowling, StateType::Escape, &ToEscapeTrigger);

		//�����Ă��鎞
		state->AddEdge(StateType::Escape, StateType::Lose, &ToLoseTrigger);

		//�^�[�Q�b�g�r����
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