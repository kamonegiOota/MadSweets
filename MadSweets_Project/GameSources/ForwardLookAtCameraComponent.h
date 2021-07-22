#pragma once

namespace basecross
{
	class ForwardLookAtCameraComponent : public Component
	{
		ex_weak_ptr<Camera> m_camera;

		void CameraSetAt()
		{
			Vec3 lookAtPosition = transform->GetWorldPosition() + transform->GetForword();
			m_camera->SetAt(lookAtPosition);
		}

	public:
		ForwardLookAtCameraComponent(std::shared_ptr<GameObject>& owner) :
			Component(owner)
		{

		}

		void OnCreate()
		{
			m_camera = GetStage()->GetView()->GetTargetCamera();

			CameraSetAt();

			m_camera->SetCameraObject(GetGameObject());
		}

		void OnUpdate2() override
		{
			CameraSetAt();
		}
	};
}