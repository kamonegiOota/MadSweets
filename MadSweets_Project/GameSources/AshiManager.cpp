/*!
@file AshiManager.cpp
@brief AshiManager�̃N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "BaseEnemy.h"
#include "AshiManager.h"

#include "AshiStator.h"
#include "AshiAnimatorCtrl.h"

#include "TargetMgr.h"

namespace basecross {

	void AshiManager::StartEscape() {
		auto stator = GetGameObject()->GetComponent<AshiStator>(false);
		if (stator) {
			stator->GetTransitionMember().escapeTrigger.Fire();
		}
	}

	void AshiManager::SuccessEscape() {
		auto stator = GetGameObject()->GetComponent<AshiStator>(false);
		if (stator) {
			stator->GetTransitionMember().loseTrigger.Fire();
		}
	}

	void AshiManager::StartReturnPlowling() {
		auto stator = GetGameObject()->GetComponent<AshiStator>(false);
		if (stator) {
			stator->GetTransitionMember().loseTrigger.Fire();
		}
	}

	void AshiManager::EndReturnPlowling() {
		auto stator = GetGameObject()->GetComponent<AshiStator>(false);
		if (stator) {
			stator->GetTransitionMember().plowlingTrigger.Fire();
		}
	}

	//�R���W��������
	void AshiManager::OnCollisionEnter(std::shared_ptr<GameObject>& other) {
				
	}

}

//endbasecross