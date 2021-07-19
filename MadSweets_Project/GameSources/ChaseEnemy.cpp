/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "ChaseEnemy.h"

#include "EnState_TargetChase.h"
#include "EnState_Plowling.h"
#include "EnState_LoseTarget.h"
#include "DebugObject.h"

namespace basecross {

	void ChaseEnemy::OnCreate() {
		ChangeStateMachine<EnState_Plowling>();
	}

	void ChaseEnemy::OnUpdate() {
		if (m_stateMachine) {
			m_stateMachine->OnUpdate();
		}
	}

	void ChaseEnemy::ChangeChaseState(const std::shared_ptr<GameObject>& target) {
		ChangeStateMachine<EnState_TargetChase>(target);
	}

	void ChaseEnemy::ChangeTargetLostState() {
		ChangeStateMachine<EnState_LoseTarget>();
	}

}

//endbasecross