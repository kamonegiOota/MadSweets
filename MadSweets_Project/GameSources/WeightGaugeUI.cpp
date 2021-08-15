/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

#include "WeightGaugeUI.h"
#include "WeightGaugeCtrl.h"

namespace basecross {

	std::shared_ptr<UIObject> WeightGaugeUI::CreateUI(const wstring& texture) {
		auto ui = GetStage()->Instantiate<UIObject>(Vec3(0.0f), Quat::Identity(), GetThis<UIObject>());
		auto image = ui->AddComponent<Image>();
		image->SetTextureResource(texture);
		image->SetFillType(ImageFillType::Vertical);

		auto rectTrans = ui->GetComponent<RectTransform>();
		rectTrans->SetRectSize(128.0f, 128.0f);

		rectTrans->SetAnchor(AnchorType::Center);
		rectTrans->SetPivot(0.0f, 0.0f);
		rectTrans->SetPosition(-550.0f, 250.0f);

		return ui;
	}

	void WeightGaugeUI::OnCreate() {
		auto gauge = CreateUI(L"NomalGauge_Tx");
		auto frame = CreateUI(L"NomalFont_Tx");
		gauge->GetComponent<Image>()->SetBlendState(BlendState::Additive);

		AddComponent<WeightGaugeCtrl>(frame,gauge);
		//auto rectTrans = GetComponent<RectTransform>();
		//rectTrans->SetAnchor(AnchorType::Center);
		//rectTrans->SetPivot(0.0f, 0.0f);
		//rectTrans->SetPosition(-550.0f, 250.0f);
	}

}

//endbasecross