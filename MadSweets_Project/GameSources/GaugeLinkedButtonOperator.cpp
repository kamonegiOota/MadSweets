#include"GaugeLinkedButtonOperator.h"
#include"GaugeManager.h"

namespace basecross
{
	GaugeLinkedButtonOperator::GaugeLinkedButtonOperator(std::shared_ptr<GameObject>& owner, const std::shared_ptr<GaugeManager>& gaugeManager) :
		Component(owner),
		m_gaugeManager(gaugeManager)
	{

	}

	void GaugeLinkedButtonOperator::SetGaugeValume(const float valume)
	{
		m_gaugeManager->SetNowGauge(valume);
	}

	float GaugeLinkedButtonOperator::GetGaugeValume() const
	{
		return m_gaugeManager->GetNowGauge();
	}

	void GaugeLinkedButtonOperator::OnUpdate()
	{
		gaugeUpdateEvent(m_gaugeManager->GetNowGauge());
	}
}