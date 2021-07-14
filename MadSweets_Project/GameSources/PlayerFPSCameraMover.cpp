#include"PlayerFPSCameraMover.h"
#include"PlayerInputer.h"

namespace basecross
{
	PlayerFPSCameraMover::PlayerFPSCameraMover(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{
		
	}

	void PlayerFPSCameraMover::SetMaxRotY(const float rotY)
	{
		m_maxRotY = std::fmaxf(m_minRotY, rotY);
	}

	void PlayerFPSCameraMover::SetMinRotY(const float rotY)
	{
		m_minRotY = std::fminf(m_maxRotY, rotY);
	}

	float PlayerFPSCameraMover::GetMaxRotY() const
	{
		return m_maxRotY;
	}

	float PlayerFPSCameraMover::GetMinRotY() const
	{
		return m_minRotY;
	}

	void PlayerFPSCameraMover::OnCreate()
	{
		m_targetCamera = GetStage()->GetView()->GetTargetCamera();

		m_lookAtObject = GetStage()->AddGameObject<GameObject>();
		m_lookAtObject->SetParent(GetGameObject());

		m_lookAtObject->GetComponent<Transform>()->SetPosition(0, 0, 1);

		m_targetCamera->SetAt(m_lookAtObject->GetComponent<Transform>()->GetWorldPosition());

		m_targetCamera->SetCameraObject(GetGameObject());
	}

	void PlayerFPSCameraMover::OnUpdate()
	{
		auto rotation = PlayerInputer::GetCameraRotation();

		m_rotY += rotation.y;

		m_rotY = MyMath::Clamp(m_rotY, m_minRotY, m_maxRotY);

		transform->SetRotation(m_rotY, 0, 0);

		m_targetCamera->SetAt(m_lookAtObject->GetComponent<Transform>()->GetWorldPosition());
	}
}