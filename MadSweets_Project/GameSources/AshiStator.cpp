/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "AshiStator.h"

namespace basecross {

	using StateType = AshiStateType;
	using TransitionMember = AshiStateTransitionMember;

	//�J�ڏ���-------------------------------------------------------------

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