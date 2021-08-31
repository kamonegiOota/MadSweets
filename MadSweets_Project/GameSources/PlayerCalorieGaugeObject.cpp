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
		auto image = AddComponent<Image>();

		auto childUI = GetStage()->Instantiate<UIObject>(Vec3(), Quat::Identity(), GetThis<UIObject>());

		auto gaugeBackgroundImage = childUI->AddComponent<Image>();

		childUI = GetStage()->Instantiate<UIObject>(Vec3(), Quat::Identity(), GetThis<UIObject>());
		
		auto rectTransform = childUI->GetComponent<RectTransform>();
		rectTransform->SetPosition(50.0f, 0.0f);

		auto gaugeImage = childUI->AddComponent<Image>();

		auto gaugeManager = AddComponent<GaugeManager>(gaugeImage, gaugeBackgroundImage);

		gaugeManager->SetGaugeRectSize(100, 100);

		rectTransform = GetComponent<RectTransform>();
		rectTransform->SetAnchor(AnchorType::LeftUp);
		rectTransform->SetPosition(200, -50);
		gaugeManager->SetGaugeImage(L"WeightGaugeColor");
		gaugeManager->SetGaugeBackgroundImage(L"WeightGaugeBackground");
		gaugeManager->SetGaugeRectSize(768 * 0.5f, 256 * 0.5f);

		GetStage()->SetSharedGameObject(L"PlayerCalorieGauge", GetThis<PlayerCalorieGaugeObject>());
	}
}