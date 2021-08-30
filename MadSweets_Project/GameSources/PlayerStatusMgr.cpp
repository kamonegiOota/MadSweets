/*!
@file PositionDrawComp.h
@brief PositionDrawComp
�S���ҁF�ێR �T��
*/

#include "stdafx.h"
#include "Project.h"
#include "PlayerStatusMgr.h"

#include "DebugObject.h"

#include "MyUtility.h"
#include "AlphaFadeCtrl.h"

namespace basecross {

	void PlayerStatusMgr::ChangeGameOverStage() {
		float stayTime(0.0f); //�X�e�[�W�J�ڂ���ꍇ�ɑ҂���
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