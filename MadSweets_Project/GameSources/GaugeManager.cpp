#include"GaugeManager.h"
#include"MathHelper.h"

using itbs::Math::MyMath;

namespace basecross
{
	GaugeManager::GaugeManager(std::shared_ptr<GameObject>& owner, std::shared_ptr<Image>& gaugeImage,
		std::shared_ptr<Image>& gaugeBackgroundImage) :
		Component(owner),
		m_gaugeImage(gaugeImage),
		m_gaugeBackgroundImage(gaugeBackgroundImage)
	{
		m_gaugeImage->SetFillType(ImageFillType::Horizontal);
	}

	void GaugeManager::UpdateGauge()
	{
		float gaugeFill = m_nowGauge / m_maxGauge;

		m_gaugeImage->SetFillAmount(gaugeFill);
	}

	void GaugeManager::SetGaugeImage(const std::wstring& imageKey)
	{
		m_gaugeImage->SetTextureResource(imageKey);
	}

	void GaugeManager::SetGaugeBackgroundImage(const std::wstring& imageKey)
	{
		m_gaugeBackgroundImage->SetTextureResource(imageKey);
	}

	void GaugeManager::SetGaugeRectSize(const float width, const float height)
	{
		m_gaugeImage->GetGameObject()->GetComponent<RectTransform>()->SetRectSize(width, height);

		m_gaugeBackgroundImage->GetGameObject()->GetComponent<RectTransform>()->SetRectSize(width, height);
	}

	void GaugeManager::SetMaxGauge(const float maxGauge)
	{
		m_maxGauge = maxGauge;

		SetNowGauge(m_nowGauge);

		UpdateGauge();
	}

	float GaugeManager::GetMaxGauge() const
	{
		return m_maxGauge;
	}

	void GaugeManager::SetNowGauge(const float nowGauge)
	{
		m_nowGauge = MyMath::Clamp(nowGauge, 0.0f, m_maxGauge);

		UpdateGauge();
	}

	float GaugeManager::GetNowGauge() const
	{
		return m_nowGauge;
	}

	void GaugeManager::AddGaugeValue(const float gaugeValue)
	{
		SetNowGauge(m_nowGauge + gaugeValue);
	}

	void GaugeManager::SetGaugeFillType(const ImageFillType imageFillType)
	{
		m_gaugeImage->SetFillType(imageFillType);
	}

	void GaugeManager::OnCreate()
	{
	}

	void GaugeManager::OnUpdate()
	{

	}
}