/*!
@file SearchObject.cpp
@brief SearchObjectなど実体
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
#include "PlayerInputer.h"

namespace basecross {

	using itbs::Input::KeyCode;
	using itbs::Input::XInputCode;

	void EventSprite::ChangeStage() {
		float stayTime(0.0f); //ステージ遷移する場合に待つ時間
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
		m_isEnd = true;

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

	void EventSprite::InputProcess() {
		if (m_isEnd) {
			return;
		}

		if (PlayerInputer::IsDecision()) {
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
			InputProcess();
		}
	}

	void EventSprite::EventStart() {
		NextSprite();
		m_isUpdate = true;
	}

}

//endbasecross