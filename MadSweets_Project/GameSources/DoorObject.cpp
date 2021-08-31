#include"DoorObject.h"
#include"EventedComponent.h"

#include "BuildeVertexPCTSprite.h"
#include "BillBoard.h"

namespace basecross
{
	DoorObject::DoorObject(std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{

	}

	void DoorObject::OnCreate()
	{
		auto texture = L"DoorObj_Tx";
		auto build = BuildeVertexPCTSprite(BuildeVertexPCTParam(texture, false));

		auto draw = AddComponent<PCTStaticDraw>();
		draw->CreateOriginalMesh(build.m_vertices, build.m_indices);
		draw->SetOriginalMeshUse(true);
		draw->SetTextureResource(texture);
		auto colorf = 0.2f;
		draw->SetDiffuse(Col4(colorf, colorf, colorf,1.0f));

		transform->SetScale(Vec3(3.0f, 4.0f, 1.0f));
		transform->Rotate(Vec3(0.0f, XM_PIDIV4, 0.0f));

		SetAlphaActive(true);

		//AddComponent<BillBoard>();

		auto col = AddComponent<CollisionSphere>();
		col->SetFixed(true);

		AddComponent<EventedComponent>();
	}
}