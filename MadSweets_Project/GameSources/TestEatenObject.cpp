#include"TestEatenObject.h"
#include"EatenComponent.h"

namespace basecross
{
	TestEatenObject::TestEatenObject(std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{

	}

	void TestEatenObject::OnCreate()
	{
		auto draw = AddComponent<PCTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_SPHERE");
		draw->SetDiffuse(Col4(1, 0, 0, 1));
		auto collision = AddComponent<CollisionObb>();

		AddComponent<EatenComponent>(10);
	}
}