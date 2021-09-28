/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
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

#include "StatorBase.h"
#include "Trigger.h"
#include "BaseEnemy.h"
#include "EnemyMainStateMachine.h"
#include "ChaseEnemyStator.h"

namespace basecross {

	void ChaseEnemy::OnCreate() {
		//ChangeStateMachine<EnState_Plowling>();
	}

	void ChaseEnemy::OnUpdate() {
		//if (m_stateMachine) {
		//	m_stateMachine->OnUpdate();
		//}
	}

	//void ChaseEnemy::ChangeChaseState(const std::shared_ptr<GameObject>& target) {
	//	auto attack = dynamic_pointer_cast<EnState_Attack>(m_stateMachine);
	//	if (attack) {
	//		return;
	//	}



		//ステートマシン変更時
		//auto stator = GetGameObject()->GetComponent<ChaseEnemyStator>(false);
		//if (stator) {
		//	stator->GetTransitionMember().chaseTrigger.Fire();
		//}
		//ChangeStateMachine<EnState_TargetChase>(target);
	//}

	//void ChaseEnemy::ChangeTargetLostState(const std::shared_ptr<GameObject>& target) {
	//	//ステートマシン変更時
	//	//auto stator = GetGameObject()->GetComponent<ChaseEnemyStator>(false);
	//	//if (stator) {
	//	//	stator->GetTransitionMember().probeTrigger.Fire();
	//	//}
	//	//ChangeStateMachine<EnState_ProbTarget>(target);
	//}

}

//endbasecross