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

	void TitleFadeCtrl::FadeStart() {
		//欲しい情報の取得
		auto nameCtrl = maru::MyUtility::GetComponent<TitleNameCtrl>();
		auto fadeCtrl = maru::MyUtility::GetComponent<FadeChocoCtrl>();

		//それぞれの終了時に呼び出したい関数セット
		nameCtrl->FadeStart();
		nameCtrl->AddEndAction(fadeCtrl, &FadeChocoCtrl::FadeStart);
		fadeCtrl->AddEndAction(GetThis<TitleFadeCtrl>(), &TitleFadeCtrl::ChangeStage);
		
		//後処理
		m_titleNameCtrl = nameCtrl;
		m_fadeChocoCtrl = fadeCtrl;
	}

}

//endbasecross