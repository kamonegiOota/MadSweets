#pragma once

namespace basecross
{
	class GameItemKeyObject : public GameObject
	{
	public:
		GameItemKeyObject(std::shared_ptr<Stage>& stage);

		void OnCreate() override;
	};
}