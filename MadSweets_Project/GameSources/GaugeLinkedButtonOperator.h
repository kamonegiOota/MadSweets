#pragma once

namespace basecross
{
	class GaugeManager;
	
	class GaugeLinkedButtonOperator : public Component
	{
		ex_weak_ptr<GaugeManager> m_gaugeManager;

	public:
		itbs::Utility::Delegate<void(const float)> gaugeUpdateEvent;

		GaugeLinkedButtonOperator(std::shared_ptr<GameObject>& owner, const std::shared_ptr<GaugeManager>& gaugeManager);

		void SetGaugeValume(const float valume);

		float GetGaugeValume() const;

		void OnUpdate() override;
	};
}