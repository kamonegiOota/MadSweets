#pragma once
#include"GaugeManager.h"

namespace basecross
{
	enum class PlayerWeightState
	{
		Fat,
		Skinny,
		Hunger
	};

	class PlayerWeightManager : public Component
	{
		float m_maxWeight = 100.0f;

		float m_nowWeight = m_maxWeight;

		const float m_skinnyLine;
		const float m_fatLine;

		PlayerWeightState m_playerWeightState;

		ex_weak_ptr<GaugeManager> m_gaugeManager;

		void UpdateGauge();
	public:
		PlayerWeightManager(std::shared_ptr<GameObject>& owner);

		void SetMaxWeight(const float maxWeight);

		float GetMaxWeight() const;

		void SetNowWeight(const float weight);

		float GetNowWeight() const;

		void AddWeight(const float weight);

		void SetGaugeManager(const std::shared_ptr<GaugeManager>& gaugeManager);

		void OnCreate() override;

		void OnUpdate() override {}
	};
}