#include"PlayerObject.h"
#include"PlayerInputer.h"
#include"PlayerMover.h"
#include"PlayerProvider.h"
#include"PlayerCameraObject.h"
#include"PlayerStanceManager.h"

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

		AddComponent<PlayerMover>();
		AddComponent<PlayerProvider>();
		AddComponent<PlayerStanceManager>();

		GetStage()->Instantiate<PlayerCameraObject>(Vec3(),Quat::Identity(),GetThis<GameObject>());
	}

	void PlayerObject::OnUpdate()
	{

	}
}