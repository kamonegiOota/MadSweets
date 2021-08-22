/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "AlphaFadeCtrl.h"

namespace basecross {

	void AlphaFadeCtrl::SetStartImageAlpha(const float& alpha) {
		auto image = m_fadeObj->GetComponent<Image>();
		image->SetAlpha(alpha);
	}

	void AlphaFadeCtrl::EndProcess() {
		m_isUpdate = false;
		m_endAction();
	}

	void AlphaFadeCtrl::FadeUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();
		auto image = m_fadeObj->GetComponent<Image>();

		auto alpha = image->GetAlpha();
		alpha += delta * m_speed * m_direct;

		if (m_isEndFunc(alpha)) {
			EndProcess();
		}

		image->SetAlpha(alpha);
	}

	void AlphaFadeCtrl::OnCreate() {
		auto fadeObj = GetStage()->Instantiate<UIObject>();
		auto image = fadeObj->AddComponent<Image>();
		image->SetTextureResource(L"FadeChoco_Tx");
		image->SetAlpha(0.0f);

		auto rectTrans = fadeObj->GetComponent<RectTransform>();
		rectTrans->SetRectSize(1280.0f, 800.0f);

		m_fadeObj = fadeObj;
	}

	void AlphaFadeCtrl::OnUpdate() {
		if (m_isUpdate) {
			FadeUpdate();
		}
	}

	void AlphaFadeCtrl::FadeInStart() {
		m_isUpdate = true;
		m_direct = -1.0f;
		SetStartImageAlpha(1.0f);

		m_isEndFunc = [](float& alpha){ 
			if (alpha < 0.0f) {
				alpha = 0.0f;
				return true;
			}
			else {
				return false;
			}
		};
	}

	void AlphaFadeCtrl::FadeOutStart() {
		m_isUpdate = true;
		m_direct = 1.0f;
		SetStartImageAlpha(0.0f);

		m_isEndFunc = [](float& alpha) {
			if (alpha > 1.0f) {
				alpha = 1.0f;
				return true;
			}
			else {
				return false;
			}
		};
	}

}

//endbasecross