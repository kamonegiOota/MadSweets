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

	using itbs::Utility::Delegate;

	void TitleFadeCtrl::ChangeStage() {
		float stayTime(0.0f); //ステージ遷移する場合に待つ時間
		PostEvent(stayTime, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMargeTestStage");
	}

	void TitleFadeCtrl::FadeChocoMgr() {
		if (m_fadeChocoCtrl->IsEnd()) {
			ChangeStage();
			m_updateFunc = nullptr;
		}
	}

	void TitleFadeCtrl::TitleNameMgr() {
		if(m_titleNameCtrl->IsEnd()) {
			m_fadeChocoCtrl->FadeStart();
			m_updateFunc = &TitleFadeCtrl::FadeChocoMgr;
		}
	}

	void TitleFadeCtrl::OnUpdate() {
		if (m_updateFunc) {
			m_updateFunc(*this);
		}
	}

	void TitleFadeCtrl::FadeStart() {
		//欲しい情報の取得
		m_titleNameCtrl = maru::MyUtility::GetComponent<TitleNameCtrl>();
		auto fadeCtrl = maru::MyUtility::GetComponent<FadeChocoCtrl>();

		//それぞれの終了時に呼び出したい関数セット
		m_titleNameCtrl->FadeStart();
		m_titleNameCtrl->AddEndAction<FadeChocoCtrl>(fadeCtrl, &FadeChocoCtrl::FadeStart);
		fadeCtrl->AddEndAction(GetThis<TitleFadeCtrl>(), &TitleFadeCtrl::ChangeStage);
		
		//後処理
		//m_updateFunc = &TitleFadeCtrl::TitleNameMgr;
		m_fadeChocoCtrl = fadeCtrl;
	}

}

//endbasecross