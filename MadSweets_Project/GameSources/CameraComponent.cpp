#include"CameraComponent.h"

namespace basecross
{
	CameraComponent::CameraComponent(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{
	}

	void CameraComponent::SetCameraAtForward()
	{
		auto forward = transform->GetForword();
		auto rotation = transform->GetWorldQuaternion().toRotVec();
		m_camera->SetAt(transform->GetWorldPosition() + transform->GetForword());
	}

	void CameraComponent::OnCreate()
	{
		m_camera = GetStage()->GetView()->GetTargetCamera();

		auto cameraObject = m_camera->GetCameraObject();

		if (cameraObject)
		{
			m_isTarget = false;
			return;
		}

		m_isTarget = true;

		SetCameraAtForward();

		m_camera->SetCameraObject(GetGameObject());
	}

	void CameraComponent::OnUpdate2()
	{
		if (!m_isTarget)
		{
			return;
		}

		SetCameraAtForward();
	}

	void CameraComponent::OnEnable()
	{
		m_isTarget = true;

		m_camera->SetCameraObject(GetGameObject());
	}

	void CameraComponent::OnDisable()
	{
		if (m_camera->GetCameraObject() != nullptr && m_camera->GetCameraObject() == GetGameObject())
		{
			m_isTarget = false;
			m_camera->SetCameraObject(nullptr);
		}
	}
}