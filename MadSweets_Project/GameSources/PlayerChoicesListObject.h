#pragma once

namespace basecross
{
	class PlayerChoicesListObject : public UIObject
	{
	public:
		PlayerChoicesListObject(std::shared_ptr<Stage>& stage);

		void OnCreate();
	};
}