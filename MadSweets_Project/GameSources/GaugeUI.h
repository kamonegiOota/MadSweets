#pragma once

namespace basecross
{
	class GaugeUI : public UIObject
	{
	public:
		GaugeUI(std::shared_ptr<Stage>& stage);

		void OnCreate() override;
	};
}