#include"PlayerWeightManager.h"
#include"MathHelper.h"

using itbs::Math::MyMath;

namespace basecross
{
	PlayerWeightManager::PlayerWeightManager(std::shared_ptr<GameObject>& owner) :
		Component(owner),
		m_skinnyLinePercentage(0.3f),
		m_fatLinePercentage(0.66f)
	{
		m_nowWeight = m_maxWeight * 0.5f;
		UpdateGauge();
	}

	void PlayerWeightManager::UpdateGauge()
	{
		if (!m_gaugeManager)
		{
			return;
		}

		m_gaugeManager->SetMaxGauge(m_maxWeight);
		m_gaugeManager->SetNowGauge(m_nowWeight);

		if (m_nowWeight >= m_maxWeight * m_fatLinePercentage)
		{
			m_playerWeightState = PlayerWeightState::Fat;
			return;
		}

		if (m_nowWeight >= m_maxWeight * m_skinnyLinePercentage)
		{
			m_playerWeightState = PlayerWeightState::Skinny;
			return;
		}

		m_playerWeightState = PlayerWeightState::Hunger;
	}

	void PlayerWeightManager::SetMaxWeight(const float maxWeight)
	{
		m_maxWeight = std::fmaxf(0.0f, maxWeight);

		m_nowWeight = std::fminf(m_nowWeight, m_maxWeight);

		UpdateGauge();
	}

	float PlayerWeightManager::GetMaxWeight() const
	{
		return m_maxWeight;
	}

	void PlayerWeightManager::SetNowWeight(const float weight)
	{
		m_nowWeight = MyMath::Clamp(weight, 0.0f, m_maxWeight);

		UpdateGauge();
	}

	float PlayerWeightManager::GetNowWeight() const
	{
		return m_nowWeight;
	}

	void PlayerWeightManager::AddWeight(const float weight)
	{
		SetNowWeight(m_nowWeight + weight);
	}

	void PlayerWeightManager::SetGaugeManager(const std::shared_ptr<GaugeManager>& gaugeManager)
	{
		m_gaugeManager = gaugeManager;

		UpdateGauge();
	}

	PlayerWeightState PlayerWeightManager::GetWeightState() const
	{
		return m_playerWeightState;
	}

	void PlayerWeightManager::OnCreate()
	{

	}
 }