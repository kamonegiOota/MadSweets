/*!
@file PositionDrawComp.h
@brief PositionDrawComp
担当者：丸山 裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "PlayerStatusMgr.h"

#include "DebugObject.h"

#include "MyUtility.h"
#include "AlphaFadeCtrl.h"

namespace basecross {

	void PlayerStatusMgr::ChangeGameOverStage() {
		float stayTime(0.0f); //ステージ遷移する場合に待つ時間
		PostEvent(stayTime, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
	}

	void PlayerStatusMgr::DestProcess() {
		auto fade = maru::MyUtility::GetComponent<AlphaFadeCtrl>();
		fade->AddEndAction(GetThis<PlayerStatusMgr>(), &PlayerStatusMgr::ChangeGameOverStage);
		fade->FadeOutStart();
	}

	void PlayerStatusMgr::Damage(const float& damage) {
		m_param.hp += -damage;

		if (m_param.hp <= 0.0f) {
			m_param.hp = 0.0f;
			ChangeState(PlayerStaus::Dest);
			DestProcess();
		}
	}

	void PlayerStatusMgr::OnUpdate() {
		//DebugObject::AddFloat(m_param.hp);
	}

}

//endbasecross