#include"GaugeUI.h"
#include"GaugeManager.h"

namespace basecross
{
	GaugeUI::GaugeUI(std::shared_ptr<Stage>& stage) :
		UIObject(stage)
	{

	}


	void GaugeUI::OnCreate()
	{
		auto image = AddComponent<Image>();

		rectTransform->SetRectSize(512, 32);

		rectTransform->SetPivot(-0.5f, 0.5f);

		rectTransform->SetPosition(10, -30);

		auto childUI = GetStage()->Instantiate<UIObject>(Vec3(), Quat::Identity(), GetThis<UIObject>());

		auto gaugeBackgroundImage = childUI->AddComponent<Image>();

		childUI = GetStage()->Instantiate<UIObject>(Vec3(), Quat::Identity(), GetThis<UIObject>());

		auto gaugeImage = childUI->AddComponent<Image>();

		auto gaugeManager = AddComponent<GaugeManager>(gaugeImage, gaugeBackgroundImage);


		gaugeManager->SetGaugeImage(L"WeightGaugeColor");

		gaugeManager->SetGuageBackgroundImage(L"WeightGaugeBackground");

		gaugeManager->SetGaugeRectSize(512, 160);
	}

}