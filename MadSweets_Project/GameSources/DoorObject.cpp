#include"DoorObject.h"
#include"EventedComponent.h"

namespace basecross
{
	DoorObject::DoorObject(std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{

	}

	void DoorObject::OnCreate()
	{
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");

		auto collider = AddComponent<CollisionObb>();
		collider->SetAfterCollision(AfterCollision::None);

		AddComponent<EventedComponent>();
	}
}