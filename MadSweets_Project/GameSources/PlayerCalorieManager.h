#pragma once
#include"GaugeManager.h"

namespace basecross
{

	class PlayerCalorieManager : public Component
	{
		float m_maxCalorie = 100.0f;

		float m_nowCalorie = m_maxCalorie;

		ex_weak_ptr<GaugeManager> m_gaugeManager;

		void UpdateGauge();
	public:
		PlayerCalorieManager(std::shared_ptr<GameObject>& owner);

		void SetMaxCalorie(const float maxWeight);

		float GetMaxCalorie() const;

		void SetNowCalorie(const float weight);

		float GetNowCalorie() const;

		void AddCalorie(const float weight);

		void SetGaugeManager(const std::shared_ptr<GaugeManager>& gaugeManager);

		void OnCreate() override;

		void OnUpdate() override {}
	};
}