#include"GaugeLinkedButtonObject.h"
#include"GaugeUI.h"
#include"GaugeManager.h"
#include"OptionGaugeOperator.h"
#include"GaugeLinkedButtonEventer.h"
#include"SoundHelper.h"
#include"GaugeLinkedButtonOperator.h"

namespace basecross
{
	GaugeLinkedButtonObject::GaugeLinkedButtonObject(std::shared_ptr<Stage>& stage) :
		MenuButtonObject(stage)
	{

	}

	void GaugeLinkedButtonObject::OnCreate()
	{
		MenuButtonObject::OnCreate();

		auto gauge = GetStage()->Instantiate<GaugeUI>(Vec3(0, -75, 0), Quat::Identity(), GetThis<UIObject>());
		auto gaugeManager = gauge->GetComponent<GaugeManager>();
		gaugeManager->SetGaugeImage(L"OptionGauge_TX");
		gaugeManager->SetGaugeRectSize(750 * 0.5f, 150 * 0.5f);
		gaugeManager->SetDiffuse(Col4(0.75f, 0.75f, 0.75f, 1.0f));
		auto optionGaugeOperator = gauge->AddComponent<OptionGaugeOperator>();
		optionGaugeOperator->SetUpdateActive(false);

		auto gaugeLinkedButtonEventer = AddComponent<GaugeLinkedButtonEventer>(gaugeManager, optionGaugeOperator);
		AddComponent<GaugeLinkedButtonOperator>(gaugeManager);

		GetComponent<Button>()->pushEvent.AddFunc(gaugeLinkedButtonEventer, &GaugeLinkedButtonEventer::OnPush);
	}
}