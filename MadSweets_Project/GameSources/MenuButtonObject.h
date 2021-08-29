#pragma once

namespace basecross
{
	class MenuButtonObject : public UIObject
	{
	public:
		MenuButtonObject(std::shared_ptr<Stage>& stage);

		void OnCreate();
	};
}