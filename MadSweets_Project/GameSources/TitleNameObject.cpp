/*!
@file TitleNameObject.cpp
@brief TitleNameObjectŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "TitleNameObject.h"
#include "TitleNameCtrl.h"

namespace basecross {

	std::shared_ptr<UIObject> TitleNameObject::CreateUI(const wstring& texture) {
		auto ui = GetStage()->Instantiate<UIObject>(Vec3(0.0f),Quat::Identity(), GetThis<UIObject>());
		auto image = ui->AddComponent<Image>();
		image->SetTextureResource(texture);

		auto rectTrans = ui->GetComponent<RectTransform>();
		rectTrans->SetRectSize(512.0f, 256.0f);
		//rectTrans->SetAnchor(AnchorType::Up);

		return ui;
	}

	void TitleNameObject::OnCreate() {
		auto font = CreateUI(L"TitleFont_Tx");
		auto choco = CreateUI(L"TitleChoco_Tx");
		choco->GetComponent<Image>()->SetDiffuse(Col4(1.0f,1.0f,1.0f,0.0f));

		AddComponent<TitleNameCtrl>(font,choco);
	}

}

//endbasecross