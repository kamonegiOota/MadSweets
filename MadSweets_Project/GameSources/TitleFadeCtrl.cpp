/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
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
		float stayTime(0.0f); //�X�e�[�W�J�ڂ���ꍇ�ɑ҂���
		PostEvent(stayTime, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMargeTestStage");
	}

	void TitleFadeCtrl::FadeStart() {
		//�~�������̎擾
		auto nameCtrl = maru::MyUtility::GetComponent<TitleNameCtrl>();
		auto fadeCtrl = maru::MyUtility::GetComponent<FadeChocoCtrl>();
		auto alphaCtrl = maru::MyUtility::GetComponent<AlphaFadeCtrl>();
		auto eventSpriteCtrl = maru::MyUtility::GetComponent<EventSprite>();

		//���ꂼ��̏I�����ɌĂяo�������֐��Z�b�g
		nameCtrl->FadeOutStart();
		nameCtrl->AddEndAction(fadeCtrl, &FadeChocoCtrl::FadeOutStart);
		fadeCtrl->AddEndAction(alphaCtrl, &AlphaFadeCtrl::FadeOutStart);
		//alphaCtrl->AddEndAction(GetThis<TitleFadeCtrl>(), &TitleFadeCtrl::ChangeStage);
		alphaCtrl->AddEndAction(eventSpriteCtrl, &EventSprite::EventStart);
		alphaCtrl->AddEndAction(alphaCtrl, &AlphaFadeCtrl::FadeInStart);

		//�㏈��
		m_titleNameCtrl = nameCtrl;
		m_fadeChocoCtrl = fadeCtrl;
	}

}

//endbasecross