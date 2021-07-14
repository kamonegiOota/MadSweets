#include"PlayerCameraObject.h"
#include"PlayerFPSCameraMover.h"

namespace basecross
{
	PlayerCameraObject::PlayerCameraObject(std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{

	}

	void PlayerCameraObject::OnCreate()
	{
		auto mover = AddComponent<PlayerFPSCameraMover>();
		mover->SetMaxRotY( XM_PIDIV4);
		mover->SetMinRotY(-XM_PIDIV4);
	}

	void PlayerCameraObject::OnUpdate()
	{
	}
}