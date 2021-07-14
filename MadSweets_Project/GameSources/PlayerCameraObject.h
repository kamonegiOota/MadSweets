#pragma once

namespace basecross
{
	class PlayerCameraObject : public GameObject
	{
	public:
		PlayerCameraObject(std::shared_ptr<Stage>& stage);

		void OnCreate() override;
		void OnUpdate() override;
	};
}