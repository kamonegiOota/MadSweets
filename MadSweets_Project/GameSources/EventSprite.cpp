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

namespace basecross {

	void EventSprite::ChangeStage() {
		float stayTime(0.0f); //ステージ遷移する場合に待つ時間
		PostEvent(stayTime, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMargeTestStage");
	}

	void EventSprite::CreateImage() {
		auto ui = GetStage()->Instantiate<UIObject>();
		auto image = ui->AddComponent<Image>();

		auto rect = ui->GetComponent<RectTransform>();
		rect->SetRectSize(1280.0f, 800.0f);

		m_image = image;
		NextSprite();
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
		if (m_sprites.size() < m_index) {
			m_image->SetTextureResource(m_sprites[m_index]);
			m_index++;
		}
		else {
			EndProcess();
		}
	}

	void EventSprite::InputMgr() {
		auto& key = App::GetApp()->GetMyInputDevice()->GetKeyBoard();

		if (key.IsInputDown(itbs::Input::KeyCode::F)) {
			NextSprite();
		}
	}

	void EventSprite::OnStart() {
		CreateImage();
		CreateFadeCtrl();
	}

	void EventSprite::OnUpdate() {
		InputMgr();
	}

}

//endbasecross