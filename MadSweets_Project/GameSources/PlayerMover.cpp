#include"PlayerMover.h"
#include"PlayerInputer.h"

namespace basecross
{
	PlayerMover::PlayerMover(std::shared_ptr<GameObject>& owner) :
		Component(owner),
		m_moveSpeed(3.0f),
		m_dashPower(1.5f)
	{

	}

	void PlayerMover::SetMoveSpeed(const float moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}

	float PlayerMover::GetMoveSpeed() const
	{
		return m_moveSpeed;
	}

	void PlayerMover::SetDashPower(const float dashPower)
	{
		m_dashPower = dashPower;
	}

	float PlayerMover::GetDashPower() const
	{
		return m_dashPower;
	}

	void PlayerMover::OnUpdate()
	{
		auto rotation = PlayerInputer::GetCameraRotation();

		rotY += rotation.x;

		transform->SetRotation(0, rotY, 0);

		auto position = transform->GetPosition();
		auto move = PlayerInputer::GetMoveDirection();

		auto moveForward = transform->GetForword() * move.y;
		auto moveRight = transform->GetRight() * move.x;

		Vec3 moveVector = (moveForward + moveRight) * App::GetApp()->GetElapsedTime() * m_moveSpeed;

		if (PlayerInputer::IsDashPush())
		{
			moveVector *= m_dashPower;
		}

		position += moveVector;
		transform->SetPosition(position);
	}

}