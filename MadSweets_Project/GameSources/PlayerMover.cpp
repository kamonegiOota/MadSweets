#include"PlayerMover.h"
#include"PlayerInputer.h"

namespace basecross
{
	PlayerMover::PlayerMover(std::shared_ptr<GameObject>& owner) :
		Component(owner),
		m_standMoveSpeed(3.0f),
		m_crouchMoveSpeed(1.5f),
		m_dashPower(1.5f),
		m_dashUseWeight(0.10f)
	{

	}

	void PlayerMover::SetMoveSpeed(const float moveSpeed)
	{
		m_standMoveSpeed = moveSpeed;
	}

	float PlayerMover::GetMoveSpeed() const
	{
		return m_standMoveSpeed;
	}

	void PlayerMover::SetDashPower(const float dashPower)
	{
		m_dashPower = dashPower;
	}

	float PlayerMover::GetDashPower() const
	{
		return m_dashPower;
	}

	void PlayerMover::SetIsCameraAffected(const bool isCameraAffected)
	{
		m_isCameraAffected = isCameraAffected;
	}

	bool PlayerMover::GetIsCameraAffected() const
	{
		return m_isCameraAffected;
	}

	void PlayerMover::OnStart()
	{
		m_playerWeightManager = GetGameObject()->GetComponent<PlayerWeightManager>();
		m_camera = GetStage()->GetView()->GetTargetCamera();
	}

	void PlayerMover::OnUpdate()
	{
		Vec3 inputVector;

		auto inputMove = PlayerInputer::GetMoveDirection();

		if (inputMove.lengthSqr() == 0)
		{
			return;
		}

		inputVector.x = inputMove.x;
		inputVector.z = inputMove.y;

		Vec3 forward;
		Vec3 right;

		if (m_isCameraAffected)
		{
			Vec3 cameraForward = m_camera->GetAt() - m_camera->GetEye();
			cameraForward.y = 0;
			cameraForward.normalize();
			forward = cameraForward;
			right = Vec3(cameraForward.z, 0, -cameraForward.x);
		}
		else
		{
			forward = Vec3(0, 0, 1);
			right = Vec3(1, 0, 0);
		}

		auto moveForward = forward * inputVector.z;
		auto moveRight = right * inputVector.x;

		Vec3 moveVector = (moveForward + moveRight) * App::GetApp()->GetElapsedTime() * m_standMoveSpeed;

		if (m_playerWeightManager->GetWeightState() != PlayerWeightState::Hunger &&
			PlayerInputer::IsDashPush())
		{
			moveVector *= m_dashPower;
			m_playerWeightManager->AddWeight(-m_dashUseWeight);
		}
		
		auto position = transform->GetPosition();

		position += moveVector;
		transform->SetPosition(position);

		transform->SetForward(moveVector);
	}
}