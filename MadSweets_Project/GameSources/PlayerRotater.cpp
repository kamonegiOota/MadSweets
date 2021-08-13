#include"PlayerRotater.h"
#include"PlayerInputer.h"

namespace basecross
{
	PlayerRotater::PlayerRotater(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void PlayerRotater::OnUpdate()
	{
		auto rotation = transform->GetQuaternion().toRotVec();

		auto rotationVector = PlayerInputer::GetCameraRotation();

		transform->SetRotation(0, rotation.y + rotationVector.x, 0);
	}
}