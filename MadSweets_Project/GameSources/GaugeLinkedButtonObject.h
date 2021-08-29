#pragma once
#include"MenuButtonObject.h"

namespace basecross
{
	class GaugeLinkedButtonObject : public MenuButtonObject
	{
	public:
		GaugeLinkedButtonObject(std::shared_ptr<Stage>& stage);

		void OnCreate() override;
	};
}