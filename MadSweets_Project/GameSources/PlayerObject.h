#pragma once

namespace basecross
{
	class PlayerObject : public GameObject
	{
		float radX = 0.0f;
		float radY = 0.0f;
	public:
		PlayerObject(std::shared_ptr<Stage>& stage);

		void OnCreate() override;
		void OnUpdate() override;
	};
}