/*!
@file LoadData.cpp
@brief LoadData�̃N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"
#include "LoadStageTrigger.h"

#include "PlayerProvider.h"

namespace basecross {

	void LoadStageTrigger::ChangeStage() {
		float stayTime(0.0f); //�X�e�[�W�J�ڂ���ꍇ�ɑ҂���
		PostEvent(stayTime, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMargeTestStage");
	}

	void LoadStageTrigger::FadeStart() {
		m_chocoCtrl->AddEndAction(GetThis<LoadStageTrigger>(), &LoadStageTrigger::ChangeStage);
		m_chocoCtrl->FadeInStart();
	}

	void LoadStageTrigger::OnCreate() {
		m_chocoCtrl = GetStage()->Instantiate<GameObject>()->AddComponent<FadeChocoCtrl>();
	}

	void LoadStageTrigger::OnCollisionEnter(std::shared_ptr<GameObject>& other){
		auto player = other->GetComponent<PlayerProvider>(false);

		if (player) {
			FadeStart();
		}
	}

}

//endbacecross