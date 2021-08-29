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

		auto childUI = GetStage()->Instantiate<UIObject>(Vec3(), Quat::Identity(), GetThis<UIObject>());

		auto gaugeBackgroundImage = childUI->AddComponent<Image>();

		childUI = GetStage()->Instantiate<UIObject>(Vec3(), Quat::Identity(), GetThis<UIObject>());

		auto gaugeImage = childUI->AddComponent<Image>();

		auto gaugeManager = AddComponent<GaugeManager>(gaugeImage, gaugeBackgroundImage);

		gaugeManager->SetGaugeRectSize(100, 100);
	}

}