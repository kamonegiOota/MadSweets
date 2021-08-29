#pragma once
#include"OptionGaugeOperator.h"

namespace basecross
{
	class GaugeLinkedButtonEventer : public Component
	{
		ex_weak_ptr<Button> m_button;
		ex_weak_ptr<GaugeManager> m_gaugeManager;
		ex_weak_ptr<OptionGaugeOperator> m_optionGaugeOperator;
		
		const Col4 m_activeDiffuse = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		const Col4 m_notActiveDiffuse = Col4(0.75f, 0.75f, 0.75f, 1.0f);

		bool m_isSelectedLock = false;
	public:
		GaugeLinkedButtonEventer(std::shared_ptr<GameObject>& owner,
			const std::shared_ptr<GaugeManager>& gaugeManager,
			const std::shared_ptr<OptionGaugeOperator>& optionGaugeOperator);

		void OnCreate() override;

		void OnPush();
	};
}