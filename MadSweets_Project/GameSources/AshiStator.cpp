/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "AshiStator.h"

namespace basecross {

	using StateType = AshiStateType;
	using TransitionMember = AshiStateTransitionMember;

	//遷移条件-------------------------------------------------------------

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

	}

	void AshiStator::CreateEdges() {

	}

	void AshiStator::OnCreate() {
		m_stateMachine = make_shared<StateMachine>();

		CreateNodes();
		CreateEdges();
	}

}

//endbasecross