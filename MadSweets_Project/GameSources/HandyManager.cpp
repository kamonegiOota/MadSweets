/*!
@file HandyManager.cpp
@brief HandyManager�̃N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "BaseEnemy.h"
#include "I_Chase.h"
#include "I_Probe.h"
#include "I_Ear.h"
#include "I_ReturnPlowling.h"
#include "HandyManager.h"

#include "HandyStator.h"
#include "HandyAnimator.h"

#include "TargetManager.h"

namespace basecross {

	void HandyManager::StartChase() {
		auto stator = GetGameObject()->GetComponent<HandyStator>(false);
		if (stator) {
			stator->GetTransitionMember().chaseTrigger.Fire();
		}
	}

	void HandyManager::EndChase() {
		auto stator = GetGameObject()->GetComponent<HandyStator>(false);
		if (stator) {
			stator->GetTransitionMember().probeTrigger.Fire();
		}
	}

	void HandyManager::StartProbe() {
		auto stator = GetGameObject()->GetComponent<HandyStator>(false);
		if (stator) {
			stator->GetTransitionMember().probeTrigger.Fire();
		}
	}

	void HandyManager::EndProbe() {
		auto stator = GetGameObject()->GetComponent<HandyStator>(false);
		if (stator) {
			stator->GetTransitionMember().loseTrigger.Fire();
		}
	}

	void HandyManager::HideSearchAnimationStart() {
		//�A�j���[�V�����̍Đ�
		auto animeCtrl = GetGameObject()->GetComponent<HandyAnimatorCtrl>(false);
		if (animeCtrl) {
			auto animator = animeCtrl->GetAnimator();
			animator->GetMemberRefarence().hideSearchTrigger.Fire();
		}
	}

	void HandyManager::Listen() {
		auto stator = GetGameObject()->GetComponent<HandyStator>(false);
		if (stator) {
			stator->GetTransitionMember().soundCheckTrigger.Fire();
		}
	}

	void HandyManager::EndListen() {
		auto stator = GetGameObject()->GetComponent<HandyStator>(false);
		if (stator) {
			stator->GetTransitionMember().loseTrigger.Fire();
		}
	}

	void HandyManager::StartReturnPlowling() {
		auto stator = GetGameObject()->GetComponent<HandyStator>(false);
		if (stator) {
			stator->GetTransitionMember().loseTrigger.Fire();
		}
	}

	void HandyManager::EndReturnPlowling() {
		auto stator = GetGameObject()->GetComponent<HandyStator>(false);
		if (stator) {
			stator->GetTransitionMember().plowlingTrigger.Fire();
		}
	}

}

//endbasecross