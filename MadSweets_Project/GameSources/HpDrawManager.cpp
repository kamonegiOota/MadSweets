/*!
@file PositionDrawComp.h
@brief PositionDrawComp
�S���ҁF�ێR �T��
*/

#include "stdafx.h"
#include "Project.h"

#include "HpDrawManager.h"
#include "PlayerStatusManager.h"

namespace basecross {

	void HpDrawManager::CreateImage() {
		auto ui = GetStage()->Instantiate<UIObject>();
		auto image = ui->AddComponent<Image>();
		image->SetTextureResource(L"HpDraw_Tx");
		image->GetGameObject()->GetComponent<RectTransform>()->SetRectSize(1280.0f, 800.0f);
		image->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));

		m_image = image;
	}

	bool HpDrawManager::IsDraw(const float& ratio) {
		//hp��m_drawRatio��菬����������\������B
		return ratio < m_drawRatio ? true : false;
	}

	float HpDrawManager::CalucAlpha() {
		auto statusMgr = GetGameObject()->GetComponent<PlayerStatusManager>();
		if (!statusMgr) {
			return 0.0f;
		}

		auto hpRatio = statusMgr->CalucHPRatio();
		if (IsDraw(hpRatio)) {  //�\��������菬����������\��
			return 1.0f - (hpRatio / m_drawRatio);
		}
		else {
			return 0.0f;
		}
	}

	void HpDrawManager::ImageAlphaManager() {
		auto alpha = CalucAlpha();

		auto color = m_image->GetDiffuse();
		color.w = alpha;
		m_image->SetDiffuse(color);
	}

	void HpDrawManager::OnCreate() {
		CreateImage();
	}

	void HpDrawManager::OnUpdate() {
		ImageAlphaManager();
	}

}

//endbasecross