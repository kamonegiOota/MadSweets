#include"PlayerMover.h"
#include"PlayerInputer.h"

namespace basecross
{
	PlayerMover::PlayerMover(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

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
		position += (moveForward + moveRight) * App::GetApp()->GetElapsedTime() * 3;
		transform->SetPosition(position);
	}

}