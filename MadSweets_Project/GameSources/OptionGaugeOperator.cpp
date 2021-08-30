#include"OptionGaugeOperator.h"
#include"SoundHelper.h"
#include"GameSaveManager.h"
#include"PlayerInputer.h"

namespace basecross
{
	OptionGaugeOperator::OptionGaugeOperator(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void OptionGaugeOperator::OnCreate()
	{
		m_gaugeManager = GetGameObject()->GetComponent<GaugeManager>();

		m_gaugeManager->SetMaxGauge(1.0f);

		int i = 0;
	}

	void OptionGaugeOperator::OnUpdate()
	{
		float addGaugeValue = m_gaugeManager->GetMaxGauge() * 0.01f;

		float addGauge = 0.0f;

		if (PlayerInputer::GetInstance()->IsLeft())
		{
			addGauge += -1.0f;
		}

		if (PlayerInputer::GetInstance()->IsRight())
		{
			addGauge += +1.0f;
		}

		m_gaugeManager->AddGaugeValue(addGaugeValue * addGauge);

	}
}