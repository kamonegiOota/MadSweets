/*!
@file PositionDrawComp.h
@brief PositionDrawComp
担当者：丸山 裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "PlayerStatusManager.h"

#include "DebugObject.h"

#include "MyUtility.h"
#include "AlphaFadeCtrl.h"

#include "HitEffectManager.h"

namespace basecross {

	void PlayerStatusManager::CreateHitEffect() {
		auto hitEffectManager = GetGameObject()->GetComponent<HitEffectManager>(false);
		if (hitEffectManager) {
			hitEffectManager->Hit();
		}
	}

	void PlayerStatusManager::ChangeGameOverStage() {
		float stayTime(0.0f); //ステージ遷移する場合に待つ時間
		PostEvent(stayTime, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
	}

	void PlayerStatusManager::DestProcess() {
		auto fade = maru::MyUtility::GetComponent<AlphaFadeCtrl>();
		fade->AddEndAction(GetThis<PlayerStatusManager>(), &PlayerStatusManager::ChangeGameOverStage);
		fade->FadeOutStart();
	}

	void PlayerStatusManager::Damage(const float& damage) {
		m_param.hp += -damage;

		CreateHitEffect();  //ヒットエフェクトの生成

		if (m_param.hp <= 0.0f) {
			m_param.hp = 0.0f;
			ChangeState(PlayerStaus::Dest);
			DestProcess();
		}
	}

	void PlayerStatusManager::OnUpdate() {
		//DebugObject::AddFloat(m_param.hp);
	}

}

//endbasecross