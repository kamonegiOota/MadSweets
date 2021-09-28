/*!
@file LoadData.cpp
@brief LoadData�̃N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "I_Chase.h"
#include "I_Probe.h"
#include "I_Ear.h"
#include "I_ReturnPlowling.h"
#include "HandyManager.h"

#include "HandyStateMgr.h"

#include "TargetMgr.h"

namespace basecross {

	void HandyManager::StartChase(const std::shared_ptr<GameObject>& target) {
		auto targetMgr = GetGameObject()->GetComponent<TargetMgr>(false);
		if (targetMgr) {
			targetMgr->SetTarget(target);
		}

		auto stator = GetGameObject()->GetComponent<HandyStateMgr>(false);
		if (stator) {
			stator->GetTransitionMember().chaseTrigger.Fire();
		}
	}

	void HandyManager::EndChase(const std::shared_ptr<GameObject>& target) {
		auto stator = GetGameObject()->GetComponent<HandyStateMgr>(false);
		if (stator) {
			stator->GetTransitionMember().probeTrigger.Fire();
		}
	}

	void HandyManager::StartProbe() {
		auto stator = GetGameObject()->GetComponent<HandyStateMgr>(false);
		if (stator) {
			stator->GetTransitionMember().probeTrigger.Fire();
		}
	}

	void HandyManager::EndProbe() {
		auto stator = GetGameObject()->GetComponent<HandyStateMgr>(false);
		if (stator) {
			stator->GetTransitionMember().loseTrigger.Fire();
		}
	}

	void HandyManager::Listen() {
		auto stator = GetGameObject()->GetComponent<HandyStateMgr>(false);
		if (stator) {
			stator->GetTransitionMember().soundCheckTrigger.Fire();
		}
	}

	void HandyManager::EndListen() {
		auto stator = GetGameObject()->GetComponent<HandyStateMgr>(false);
		if (stator) {
			stator->GetTransitionMember().loseTrigger.Fire();
		}
	}

	void HandyManager::StartReturnPlowling() {
		auto stator = GetGameObject()->GetComponent<HandyStateMgr>(false);
		if (stator) {
			stator->GetTransitionMember().loseTrigger.Fire();
		}
	}

	void HandyManager::EndReturnPlowling() {
		auto stator = GetGameObject()->GetComponent<HandyStateMgr>(false);
		if (stator) {
			stator->GetTransitionMember().plowlingTrigger.Fire();
		}
	}

}

//endbasecross