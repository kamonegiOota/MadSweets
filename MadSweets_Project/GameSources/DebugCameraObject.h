#pragma once
#include"CameraHelper.h"

namespace basecross
{
	class DebugCameraObject : public GameObject
	{
		ex_weak_ptr<VirtualCamera> m_virtualCamera;
	public:
		DebugCameraObject(std::shared_ptr<Stage>& stage);

		void OnCreate() override;

		void OnUpdate() override;
	};
}