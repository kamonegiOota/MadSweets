#include"PlayerCameraObject.h"
#include"PlayerInputer.h"

namespace basecross
{
	PlayerCameraObject::PlayerCameraObject(std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{

	}

	void PlayerCameraObject::OnCreate()
	{
		lookAtObject = GetStage()->AddGameObject<GameObject>();
		lookAtObject->SetParent(GetThis<GameObject>());

		lookAtObject->GetComponent<Transform>()->SetPosition(0, 0, 1);

		camera = GetStage()->GetView()->GetTargetCamera();

		camera->SetAt(lookAtObject->GetComponent<Transform>()->GetPosition());

		camera->SetCameraObject(GetThis<GameObject>());

		int i = 0;
	}

	void PlayerCameraObject::OnUpdate()
	{
		auto rotation = PlayerInputer::GetCameraRotation();

		radX += rotation.x;
		radY += rotation.y;

		radY = MyMath::Clamp(radY, -XM_PIDIV4 * 0.25, XM_PIDIV4 * 0.25);

		transform->SetRotation(radY, radX, 0);

		camera->SetAt(lookAtObject->GetComponent<Transform>()->GetWorldPosition());

	}
}