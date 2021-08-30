#pragma once

namespace basecross
{
	class GameMessageWindowObject : public UIObject
	{
	public:
		static const std::wstring SHARED_KEY;

		GameMessageWindowObject(std::shared_ptr<Stage>& stage);

		void OnCreate();
	};
}