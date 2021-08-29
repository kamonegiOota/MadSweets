#pragma once
#include"GaugeManager.h"

namespace basecross
{

	class OptionGaugeOperator : public Component
	{
		ex_weak_ptr<GaugeManager> m_gaugeManager;

	public:
		OptionGaugeOperator(std::shared_ptr<GameObject>& owner);

		void OnCreate() override;

		void OnUpdate() override;
	};
}