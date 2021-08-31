#include"PlayerCalorieGaugeObject.h"
#include"GaugeManager.h"

namespace basecross
{
	PlayerCalorieGaugeObject::PlayerCalorieGaugeObject(std::shared_ptr<Stage>& stage) :
		GaugeUI(stage)
	{

	}

	void PlayerCalorieGaugeObject::OnCreate()
	{
		GaugeUI::OnCreate();

		auto rectTransform = GetComponent<RectTransform>();
		rectTransform->SetAnchor(AnchorType::LeftUp);
		rectTransform->SetPosition(200, -50);
		auto gaugeManager = GetComponent<GaugeManager>();
		gaugeManager->SetGaugeImage(L"WeightGaugeColor");
		gaugeManager->SetGaugeBackgroundImage(L"WeightGaugeBackground");
		gaugeManager->SetGaugeRectSize(768 * 0.5f, 256 * 0.5f);

		GetStage()->SetSharedGameObject(L"PlayerCalorieGauge", GetThis<PlayerCalorieGaugeObject>());
	}
}