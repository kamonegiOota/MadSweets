#include"PlayerCalorieManager.h"
#include"MathHelper.h"

using itbs::Math::MyMath;

namespace basecross
{
	PlayerCalorieManager::PlayerCalorieManager(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{
		m_nowCalorie = m_maxCalorie * 0.5f;
		UpdateGauge();
	}

	void PlayerCalorieManager::UpdateGauge()
	{
		if (!m_gaugeManager)
		{
			return;
		}

		m_gaugeManager->SetMaxGauge(m_maxCalorie);
		m_gaugeManager->SetNowGauge(m_nowCalorie);
	}

	void PlayerCalorieManager::SetMaxCalorie(const float maxWeight)
	{
		m_maxCalorie = std::fmaxf(0.0f, maxWeight);

		m_nowCalorie = MyMath::Clamp(m_nowCalorie, 0.0f, m_maxCalorie);

		UpdateGauge();
	}

	float PlayerCalorieManager::GetMaxCalorie() const
	{
		return m_maxCalorie;
	}

	void PlayerCalorieManager::SetNowCalorie(const float weight)
	{
		m_nowCalorie = MyMath::Clamp(weight, 0.0f, m_maxCalorie);

		UpdateGauge();
	}

	float PlayerCalorieManager::GetNowCalorie() const
	{
		return m_nowCalorie;
	}

	void PlayerCalorieManager::AddCalorie(const float weight)
	{
		SetNowCalorie(m_nowCalorie + weight);
	}

	void PlayerCalorieManager::SetGaugeManager(const std::shared_ptr<GaugeManager>& gaugeManager)
	{
		m_gaugeManager = gaugeManager;

		UpdateGauge();
	}

	void PlayerCalorieManager::OnCreate()
	{

	}
 }