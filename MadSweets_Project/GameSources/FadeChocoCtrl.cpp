/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

#include "FadeChocoCtrl.h"

#include "MyUtility.h"

namespace basecross {

	void FadeChocoCtrl::CreateChocoUI() {
		m_ui = GetStage()->Instantiate<UIObject>();
		auto image = m_ui->AddComponent<Image>();
		image->SetTextureResource(L"FadeChoco_Tx");
		
		auto rectTrans = m_ui->GetComponent<RectTransform>();
		rectTrans->SetAnchor(AnchorType::Up);
		rectTrans->SetPivot(Vec2(0.0f, 1.0f));
		rectTrans->SetRectSize(m_uiSize.x, 0.0f);
	}

	void FadeChocoCtrl::FadeUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();

		auto rectTrans = m_ui->GetComponent<RectTransform>();
		auto height = rectTrans->GetHeight();
		height += m_speed * delta;

		float maxSize = 6000.0f;
		if (height >= maxSize) {
			m_isEnd = true;
			height = maxSize;
			m_updateFunc = nullptr;
		}

		rectTrans->SetHeight(height);
	}

	void FadeChocoCtrl::OnCreate() {
		CreateChocoUI();
	}

	void FadeChocoCtrl::OnUpdate() {
		if (m_updateFunc) {
			m_updateFunc(*this);
		}
	}

	void FadeChocoCtrl::FadeStart() {
		m_updateFunc = &FadeChocoCtrl::FadeUpdate;
		m_isEnd = false;
	}

}

//endbasecross