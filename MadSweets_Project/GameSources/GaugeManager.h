#pragma once

namespace basecross
{
	class GaugeManager : public Component
	{
		ex_weak_ptr<Image> m_gaugeImage;
		ex_weak_ptr<Image> m_gaugeBackgroundImage;

		float m_maxGauge = 100.0f;
		float m_nowGauge = m_maxGauge;

		void UpdateGauge();
	public:
		GaugeManager(std::shared_ptr<GameObject>& owner,std::shared_ptr<Image>& gaugeImage,std::shared_ptr<Image>& gaugeBackgroundImage);

		void SetGaugeImage(const std::wstring& imageKey);

		void SetGuageBackgroundImage(const std::wstring& imageKey);

		void SetGaugeRectSize(const float width, const float height);

		void SetMaxGauge(const float maxGauge);

		float GetMaxGauge() const;

		void SetNowGauge(const float nowGauge);

		float GetNowGauge() const;

		void AddGaugeValue(const float gaugeValue);

		void OnCreate() override;

		void OnUpdate() override;
	};
}