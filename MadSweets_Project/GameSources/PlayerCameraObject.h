#pragma once

namespace basecross
{
	class PlayerCameraObject : public GameObject
	{
		ex_weak_ptr<Camera> camera;
		ex_weak_ptr<GameObject> lookAtObject;
		float radX = 0.0f;
		float radY = 0.0f;
	public:
		PlayerCameraObject(std::shared_ptr<Stage>& stage);

		void OnCreate() override;
		void OnUpdate() override;
	};
}