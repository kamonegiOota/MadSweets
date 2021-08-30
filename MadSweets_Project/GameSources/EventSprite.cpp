/*!
@file SearchObject.cpp
@brief SearchObject�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "EventSprite.h"
#include "UIHelper.h"
#include "MyUtility.h"

#include "DebugObject.h"

#include "AlphaFadeObject.h"
#include "AlphaFadeCtrl.h"

#include "SoundHelper.h"

namespace basecross {

	void EventSprite::ChangeStage() {
		float stayTime(0.0f); //�X�e�[�W�J�ڂ���ꍇ�ɑ҂���
		PostEvent(stayTime, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMargeTestStage");
		SimpleSoundManager::StopBGM();
	}

	void EventSprite::CreateImage() {
		auto ui = GetStage()->Instantiate<UIObject>(Vec3(0.0f),Quat::Identity(), dynamic_pointer_cast<UIObject>(GetGameObject()));
		auto image = ui->AddComponent<Image>();

		auto rect = ui->GetComponent<RectTransform>();
		rect->SetRectSize(1280.0f, 800.0f);
		
		m_image = image;
	}

	void EventSprite::CreateFadeCtrl() {
		auto fade = GetGameObject()->GetStage()->Instantiate<AlphaFadeObject>();
		m_fadeCtrl = fade->GetComponent<AlphaFadeCtrl>(false);
	}

	void EventSprite::EndProcess() {
		if (m_fadeCtrl) {
			m_fadeCtrl->AddEndAction(GetThis<EventSprite>(), &EventSprite::ChangeStage);
			m_fadeCtrl->FadeOutStart();
		}
	}

	void EventSprite::NextSprite() {
		if (m_sprites.size() > m_index) {
			m_image->SetTextureResource(m_sprites[m_index]);
			m_index++;
		}
		else {
			EndProcess();
		}
	}

	void EventSprite::TimeMgr() {
		auto delta = App::GetApp()->GetElapsedTime();
		m_timeElapsed += delta;

		if (m_timeElapsed > m_time) {
			m_timeElapsed = 0.0f;
			NextSprite();
		}
	}

	void EventSprite::OnCreate() {
		CreateImage();
		CreateFadeCtrl();
	}

	void EventSprite::OnStart() {

	}

	void EventSprite::OnUpdate() {
		if (m_isUpdate) {
			TimeMgr();
		}
	}

	void EventSprite::EventStart() {
		NextSprite();
		m_isUpdate = true;
	}

}

//endbasecross