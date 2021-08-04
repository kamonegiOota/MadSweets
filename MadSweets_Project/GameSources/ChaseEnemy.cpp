/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "ChaseEnemy.h"

#include "EnState_TargetChase.h"
#include "EnState_Plowling.h"
#include "EnState_LoseTarget.h"
#include "EnState_ProbeTarget.h"
#include "EnState_Attack.h"
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
		//auto attackType = (type_index)(typeid(EnState_Attack));
		//auto nowType = (type_index)(typeid(m_stateMachine));
		//DebugObject::m_wss << to_wstring(attackType) << endl;
		auto attack = dynamic_pointer_cast<EnState_Attack>(m_stateMachine);
		if (attack) {
			return;
		}

		ChangeStateMachine<EnState_TargetChase>(target);
	}

	void ChaseEnemy::ChangeTargetLostState(const std::shared_ptr<GameObject>& target) {
		ChangeStateMachine<EnState_ProbTarget>(target);
	}

}

//endbasecross