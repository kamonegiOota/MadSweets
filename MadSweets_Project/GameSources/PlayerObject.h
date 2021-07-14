#pragma once

namespace basecross
{
	class PlayerObject : public GameObject
	{
	public:
		PlayerObject(std::shared_ptr<Stage>& stage);

		void OnCreate() override;
		void OnUpdate() override;
	};
}