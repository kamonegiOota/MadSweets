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

	void TitleFadeCtrl::FadeStart() {
		//�~�������̎擾
		auto nameCtrl = maru::MyUtility::GetComponent<TitleNameCtrl>();
		auto fadeCtrl = maru::MyUtility::GetComponent<FadeChocoCtrl>();

		//���ꂼ��̏I�����ɌĂяo�������֐��Z�b�g
		nameCtrl->FadeStart();
		nameCtrl->AddEndAction(fadeCtrl, &FadeChocoCtrl::FadeStart);
		fadeCtrl->AddEndAction(GetThis<TitleFadeCtrl>(), &TitleFadeCtrl::ChangeStage);
		
		//�㏈��
		m_titleNameCtrl = nameCtrl;
		m_fadeChocoCtrl = fadeCtrl;
	}

}

//endbasecross