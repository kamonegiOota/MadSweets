#include"DoorObject.h"
#include"EventedComponent.h"

#include "BuildeVertexPCTSprite.h"

namespace basecross
{
	DoorObject::DoorObject(std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{

	}

	void DoorObject::OnCreate()
	{
		auto param = BuildeVertexPCTParam(L"DoorObj_Tx", false);
		transform->SetScale(Vec3(1.0f,2.0f,1.0f));
		auto build = BuildeVertexPCTSprite(param);

		auto draw = AddComponent<PNTStaticDraw>();
		draw->CreateOriginalMesh(build.m_vertices, build.m_indices);
		draw->SetOriginalMeshUse(true);

		auto collider = AddComponent<CollisionObb>();
		collider->SetAfterCollision(AfterCollision::None);

		AddComponent<EventedComponent>();
	}
}