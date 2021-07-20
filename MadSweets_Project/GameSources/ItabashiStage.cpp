#include"ItabashiStage.h"
#include"PlayerObject.h"
#include"GaugeUI.h"
#include"TestEatenObject.h"

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

		std::wstring mediaDir = App::GetApp()->GetDataDirWString();
		auto& app = App::GetApp();

		std::wstring textureDir = mediaDir + L"Textures\\";
		app->RegisterTexture(L"WeightGaugeBackground", textureDir + L"WeightGaugeBackGround.png");
		app->RegisterTexture(L"WeightGaugeColor", textureDir + L"WeightGaugeColor.png");
		//モデル
		std::wstring modelDir = mediaDir + L"Models\\";
		auto modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Player\\StandStay\\", L"PlayerStandStay.bmf");
		app->RegisterResource(L"PlayerStandStay", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Player\\CrouchStay\\", L"PlayerCrouchStay.bmf");
		app->RegisterResource(L"PlayerCrouchStay", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Player\\StandToCrouch\\", L"PlayerStandToCrouch.bmf");
		app->RegisterResource(L"PlayerStandToCrouch", modelMesh);

		auto gauge = Instantiate<GaugeUI>();

		auto rectTransform = gauge->GetComponent<RectTransform>();

		rectTransform->SetAnchor(AnchorType::LeftUp);

		SetSharedGameObject(L"PlayerWeightGauge", gauge);

		auto go = Instantiate<UIObject>();
		go->GetComponent<RectTransform>()->SetPosition(300, 0);
		auto mo = go->AddComponent<ChoicesList>();

		SetSharedGameObject(L"PlayerChoicesList", go);


		auto playerObject = Instantiate<PlayerObject>();

		SetSharedGameObject(L"PlayerObject", playerObject);

		std::vector<std::shared_ptr<GameObject>> gameobjects;

		for (int i = 0; i < 4; i++)
		{
			auto gameobject = Instantiate<GameObject>();

			auto draw = gameobject->AddComponent<PNTStaticDraw>();
			draw->SetMeshResource(L"DEFAULT_CUBE");

			auto collision = gameobject->AddComponent<CollisionObb>();
			collision->SetFixed(true);
			gameobjects.push_back(gameobject);
		}

		gameobjects[0]->GetComponent<Transform>()->SetPosition(-2, 0, -2);
		gameobjects[1]->GetComponent<Transform>()->SetPosition( 2, 0, -2);
		gameobjects[2]->GetComponent<Transform>()->SetPosition(-2, 0,  2);
		gameobjects[3]->GetComponent<Transform>()->SetPosition( 2, 0,  2);

		auto testKashi = Instantiate<TestEatenObject>();

		testKashi->GetComponent<Transform>()->SetPosition(0, 0, 3);

		auto a = itbs::Utility::Delegate<void()>(GetThis<ItabashiStage>(), &ItabashiStage::OnCreate);
		itbs::Utility::Delegate<void()> b;

	}
}