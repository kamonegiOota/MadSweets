/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

#include "TitleFadeCtrl.h"

#include "TitleNameCtrl.h"

#include "MyUtility.h"

namespace basecross {

	void TitleFadeCtrl::ChangeStage() {
		float stayTime(0.0f); //ステージ遷移する場合に待つ時間
		PostEvent(stayTime, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMargeTestStage");
	}

	void TitleFadeCtrl::ChangeStageMgr() {
		if(m_titleNameCtrl->IsEnd()) {
			ChangeStage();
			m_updateFunc = nullptr;
		}
	}

	void TitleFadeCtrl::OnUpdate() {
		if (m_updateFunc) {
			m_updateFunc(*this);
		}
	}

	void TitleFadeCtrl::FadeStart() {
		m_titleNameCtrl = maru::MyUtility::GetComponent<TitleNameCtrl>();
		m_titleNameCtrl->FadeStart();

		m_updateFunc = &TitleFadeCtrl::ChangeStageMgr;
	}

}

//endbasecross