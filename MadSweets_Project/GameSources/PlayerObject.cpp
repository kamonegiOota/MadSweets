#include"PlayerObject.h"
#include"PlayerInputer.h"

namespace basecross
{
	PlayerObject::PlayerObject(std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{

	}

	void PlayerObject::OnCreate()
	{
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");

		PlayerInputer::SetRotationSensitivityLevel(10);
	}

	void PlayerObject::OnUpdate()
	{
		auto position = transform->GetPosition();
		auto move= PlayerInputer::GetMoveDirection();
		position += Vec3(move.x, 0, move.y) * App::GetApp()->GetElapsedTime() * 3;
		transform->SetPosition(position);

		auto rotation = PlayerInputer::GetCameraRotation();

		//transform->Rotate(0,rotation.x, 0);


	}
}