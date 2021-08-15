/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

#include "TitleNameCtrl.h"

namespace basecross {

	void TitleNameCtrl::UpdateChoco() {
		auto delta = App::GetApp()->GetElapsedTime();
		auto image = m_chocoUI->GetComponent<Image>();
		auto rectTrans = m_chocoUI->GetComponent<RectTransform>();

		auto color = image->GetDiffuse();
		color.w += m_speed * delta;

		if (color.w >= 1.0f) {
			color.w = 1.0f;
			EndProcess();
		}

		image->SetDiffuse(color);
	}

	void TitleNameCtrl::EndProcess() {
		m_updateFunc = nullptr;
		m_isEnd = true;

		m_endAction();
		m_endAction.Clear();
	}

	void TitleNameCtrl::OnCreate() {
		//auto rectTrans = m_fontUI->GetComponent<RectTransform>();
		//auto width = rectTrans->GetWidth();
		//auto height = rectTrans->GetHeight();
		//m_size = Vec2(width, height);
	}

	void TitleNameCtrl::OnUpdate() {
		if (m_updateFunc) {
			m_updateFunc(*this);
		}
	}

	void TitleNameCtrl::FadeOutStart() {
		m_isEnd = false;
		m_updateFunc = &TitleNameCtrl::UpdateChoco;
	}

}

//endbasecross