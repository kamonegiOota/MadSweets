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
		//�~�������̎擾
		m_titleNameCtrl = maru::MyUtility::GetComponent<TitleNameCtrl>();
		auto fadeCtrl = maru::MyUtility::GetComponent<FadeChocoCtrl>();

		//���ꂼ��̏I�����ɌĂяo�������֐��Z�b�g
		m_titleNameCtrl->FadeStart();
		m_titleNameCtrl->AddEndAction<FadeChocoCtrl>(fadeCtrl, &FadeChocoCtrl::FadeStart);
		fadeCtrl->AddEndAction(GetThis<TitleFadeCtrl>(), &TitleFadeCtrl::ChangeStage);
		
		//�㏈��
		//m_updateFunc = &TitleFadeCtrl::TitleNameMgr;
		m_fadeChocoCtrl = fadeCtrl;
	}

}

//endbasecross