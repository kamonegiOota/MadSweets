#pragma once
#include"GaugeUI.h"

namespace basecross
{
	class PlayerCalorieGaugeObject : public GaugeUI
	{
	public:
		PlayerCalorieGaugeObject(std::shared_ptr<Stage>& stage);

		void OnCreate();
	};
}