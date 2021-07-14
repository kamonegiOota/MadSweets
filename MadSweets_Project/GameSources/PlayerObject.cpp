#include"PlayerObject.h"
#include"PlayerInputer.h"
#include"PlayerMover.h"

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
	}

	void PlayerObject::OnUpdate()
	{

	}
}