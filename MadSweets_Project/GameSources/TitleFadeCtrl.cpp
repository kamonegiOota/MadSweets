/*!
@file TitleFadeCtrl.cpp
@brief TitleFadeCtrl実体
*/

#include "stdafx.h"
#include "Project.h"

#include "TitleFadeCtrl.h"
#include "TitleNameCtrl.h"
#include "AlphaFadeCtrl.h"
#include "EventSprite.h"

#include "MyUtility.h"

namespace basecross {

	void TitleFadeCtrl::ChangeStage() {
		float stayTime(0.0f); //ステージ遷移する場合に待つ時間
		PostEvent(stayTime, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMargeTestStage");
	}

	void TitleFadeCtrl::FadeStart() {
		//欲しい情報の取得
		auto nameCtrl = maru::MyUtility::GetComponent<TitleNameCtrl>();
		auto fadeCtrl = maru::MyUtility::GetComponent<FadeChocoCtrl>();
		auto alphaCtrl = maru::MyUtility::GetComponent<AlphaFadeCtrl>();
		auto eventSpriteCtrl = maru::MyUtility::GetComponent<EventSprite>();

		//それぞれの終了時に呼び出したい関数セット
		nameCtrl->FadeOutStart();
		nameCtrl->AddEndAction(fadeCtrl, &FadeChocoCtrl::FadeOutStart);
		fadeCtrl->AddEndAction(alphaCtrl, &AlphaFadeCtrl::FadeOutStart);
		//alphaCtrl->AddEndAction(GetThis<TitleFadeCtrl>(), &TitleFadeCtrl::ChangeStage);
		alphaCtrl->AddEndAction(eventSpriteCtrl, &EventSprite::EventStart);
		alphaCtrl->AddEndAction(alphaCtrl, &AlphaFadeCtrl::FadeInStart);

		//後処理
		m_titleNameCtrl = nameCtrl;
		m_fadeChocoCtrl = fadeCtrl;
	}

}

//endbasecross