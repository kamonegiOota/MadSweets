#include"ItabashiStage.h"
#include"PlayerObject.h"

namespace basecross
{
	void ItabashiStage::OnCreate()
	{
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();

		auto playerObject = Instantiate<PlayerObject>();

		std::vector<std::shared_ptr<GameObject>> gameobjects;

		for (int i = 0; i < 4; i++)
		{
			auto gameobject = Instantiate<GameObject>();

			auto draw = gameobject->AddComponent<PNTStaticDraw>();
			draw->SetMeshResource(L"DEFAULT_CUBE");

			gameobjects.push_back(gameobject);
		}

		gameobjects[0]->GetComponent<Transform>()->SetPosition(-2, 0, -2);
		gameobjects[1]->GetComponent<Transform>()->SetPosition( 2, 0, -2);
		gameobjects[2]->GetComponent<Transform>()->SetPosition(-2, 0,  2);
		gameobjects[3]->GetComponent<Transform>()->SetPosition( 2, 0,  2);
	}
}