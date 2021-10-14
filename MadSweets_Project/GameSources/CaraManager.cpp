/*!
@file CaraManager.cpp
@brief CaraManagerのクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "I_Chase.h"
#include "I_Probe.h"
#include "I_Ear.h"
#include "I_ReturnPlowling.h"
#include "CaraManager.h"

#include "CaraStator.h"
#include "CaraAnimatorCtrl.h"

#include "TargetMgr.h"

namespace basecross {

	void CaraManager::StartChase() {
		//auto targetMgr = GetGameObject()->GetComponent<TargetMgr>(false);
		//if (targetMgr && target != nullptr) {
		//	targetMgr->SetTarget(target);
		//}

		auto stator = GetGameObject()->GetComponent<CaraStator>(false);
		if (stator) {
			stator->GetTransitionMember().chaseTrigger.Fire();
		}
	}

	void CaraManager::EndChase() {
		auto stator = GetGameObject()->GetComponent<CaraStator>(false);
		if (stator) {
			stator->GetTransitionMember().probeTrigger.Fire();
		}
	}

	void CaraManager::StartProbe() {
		auto stator = GetGameObject()->GetComponent<CaraStator>(false);
		if (stator) {
			stator->GetTransitionMember().probeTrigger.Fire();
		}
	}

	void CaraManager::EndProbe() {
		auto stator = GetGameObject()->GetComponent<CaraStator>(false);
		if (stator) {
			stator->GetTransitionMember().loseTrigger.Fire();
		}
	}

	void CaraManager::HideSearchAnimationStart() {
		//アニメーションの再生
		auto animeCtrl = GetGameObject()->GetComponent<CaraAnimatorCtrl>(false);
		if (animeCtrl) {
			animeCtrl->GetAnimator()->GetMemberRefarence().hideSearchTrigger.Fire();
		}
	}

	void CaraManager::Listen() {
		auto stator = GetGameObject()->GetComponent<CaraStator>(false);
		if (stator) {
			stator->GetTransitionMember().soundCheckTrigger.Fire();
		}
	}

	void CaraManager::EndListen() {
		auto stator = GetGameObject()->GetComponent<CaraStator>(false);
		if (stator) {
			stator->GetTransitionMember().loseTrigger.Fire();
		}
	}

	void CaraManager::StartReturnPlowling() {
		auto stator = GetGameObject()->GetComponent<CaraStator>(false);
		if (stator) {
			stator->GetTransitionMember().loseTrigger.Fire();
		}
	}

	void CaraManager::EndReturnPlowling() {
		auto stator = GetGameObject()->GetComponent<CaraStator>(false);
		if (stator) {
			stator->GetTransitionMember().plowlingTrigger.Fire();
		}
	}

}

//endbasecross