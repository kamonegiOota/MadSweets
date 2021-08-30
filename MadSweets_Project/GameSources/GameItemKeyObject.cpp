#include"GameItemKeyObject.h"
#include"GottenComponent.h"
#include"BuildeVertexPCTSprite.h"
#include"BillBoard.h"

namespace basecross
{
	GameItemKeyObject::GameItemKeyObject(std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{

	}

	void GameItemKeyObject::OnCreate()
	{
		auto build = BuildeVertexPCTSprite(BuildeVertexPCTParam(L"DoorKey_Tx", false));

		auto draw = AddComponent<PCTStaticDraw>();
		draw->CreateOriginalMesh(build.m_vertices, build.m_indices);
		draw->SetOriginalMeshUse(true);
		draw->SetTextureResource(L"DoorKey_Tx");

		SetAlphaActive(true);

		AddComponent<BillBoard>();

		auto col = AddComponent<CollisionSphere>();
		col->SetFixed(true);

		AddComponent<GottenComponent>(GameItem(L"Key"));
	}
}