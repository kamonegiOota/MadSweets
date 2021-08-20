#include"TestEatenObject.h"
#include"EatenComponent.h"
#include"SoundHelper.h"
#include"PlayerInputer.h"

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

		AddComponent<EatenComponent>(EatenData(10, 10));

		AddComponent<SoundEmitter>();
	}

	void TestEatenObject::OnUpdate()
	{
	}
}