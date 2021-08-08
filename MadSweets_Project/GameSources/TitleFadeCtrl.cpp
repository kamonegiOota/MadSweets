/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

#include "TitleFadeCtrl.h"

#include "TitleNameCtrl.h"

#include "MyUtility.h"

namespace basecross {

	using itbs::Utility::Delegate;

	void TitleFadeCtrl::ChangeStage() {
		float stayTime(0.0f); //�X�e�[�W�J�ڂ���ꍇ�ɑ҂���
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
		m_titleNameCtrl = maru::MyUtility::GetComponent<TitleNameCtrl>();
		m_titleNameCtrl->FadeStart();

		auto fadeCtrl = maru::MyUtility::GetComponent<FadeChocoCtrl>();

		auto deleg = Delegate<void()>();
		deleg.AddFunc<FadeChocoCtrl>(fadeCtrl, &FadeChocoCtrl::FadeStart);
		m_titleNameCtrl->SetDelegate(deleg);

		//m_updateFunc = &TitleFadeCtrl::TitleNameMgr;
	}

}

//endbasecross