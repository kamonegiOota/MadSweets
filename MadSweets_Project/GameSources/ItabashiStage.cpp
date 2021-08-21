#include"ItabashiStage.h"
#include"PlayerObject.h"
#include"GaugeUI.h"
#include"TestEatenObject.h"
#include"FontHelper.h"
#include"SoundHelper.h"
#include"HiddenComponent.h"
#include"ParticleSystem.h"
#include"GaugeManager.h"

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
		app->RegisterTexture(L"HpDraw_Tx", textureDir + L"HPPinch.png");

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

		wstring SE_Dir = mediaDir + L"SEs\\";
		App::GetApp()->RegisterWav(L"Test", SE_Dir + L"Test.wav");
		App::GetApp()->RegisterWav(L"Test2", SE_Dir + L"Test2.wav");

		auto gauge = Instantiate<GaugeUI>();
		auto gaugeManager = gauge->GetComponent<GaugeManager>();

		gaugeManager->SetGaugeImage(L"WeightGaugeColor");
		gaugeManager->SetGaugeBackgroundImage(L"WeightGaugeBackground");
		gaugeManager->SetGaugeRectSize(512, 160);

		auto rectTransform = gauge->GetComponent<RectTransform>();

		rectTransform->SetAnchor(AnchorType::LeftUp);

		SetSharedGameObject(L"PlayerWeightGauge", gauge);

		auto go = Instantiate<UIObject>();
		go->GetComponent<RectTransform>()->SetPosition(300, 0);
		auto mo = go->AddComponent<ChoicesList>();
		mo->OnStart();

		SetSharedGameObject(L"PlayerChoicesList", go);


		auto playerObject = Instantiate<PlayerObject>();

		SetSharedGameObject(L"PlayerObject", playerObject);

		//std::vector<std::shared_ptr<GameObject>> gameobjects;

		//for (int i = 0; i < 4; i++)
		//{
		//	auto gameobject = Instantiate<GameObject>();

		//	auto draw = gameobject->AddComponent<PNTStaticDraw>();
		//	draw->SetMeshResource(L"DEFAULT_CUBE");

		//	auto collision = gameobject->AddComponent<CollisionObb>();
		//	collision->SetFixed(true);
		//	gameobjects.push_back(gameobject);
		//	gameobject->AddTag(L"Wall");
		//}

		//gameobjects[0]->GetComponent<Transform>()->SetPosition(-2, 0, -2);
		//gameobjects[1]->GetComponent<Transform>()->SetPosition( 2, 0, -2);
		//gameobjects[2]->GetComponent<Transform>()->SetPosition(-2, 0,  2);
		//gameobjects[3]->GetComponent<Transform>()->SetPosition( 2, 0,  2);

		auto testKashi = Instantiate<TestEatenObject>();
		auto testKashi2 = Instantiate<TestEatenObject>();

		testKashi->GetComponent<Transform>()->SetPosition(0, 0, 3);
		testKashi2->GetComponent<Transform>()->SetPosition(0.5f, 0, 3);

		auto a = itbs::Utility::Delegate<void()>(GetThis<ItabashiStage>(), &ItabashiStage::OnCreate);
		itbs::Utility::Delegate<void()> b;

		App::GetApp()->GetXAudio2Manager()->GetSoundItemVec();

		for (auto& fontName : FontHelper::GetSystemFontNames())
		{
			OutputDebugString((fontName + L"\n").c_str());
		}

		SimpleSoundManager::ChangeBGM(L"TitleBGM2", 0.1f);

		auto gameobject = Instantiate<GameObject>();
		auto trans = gameobject->GetComponent<Transform>();
		trans->SetScale(4.75f, 1.0f, 14.0f);
		trans->SetPosition(0, 0, -10);
		trans->SetRotation(0, XM_PIDIV2, XM_PIDIV2);
		auto draw = gameobject->AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");

		auto collision = gameobject->AddComponent<CollisionObb>();
		collision->SetFixed(true);
		gameobject->AddTag(L"Wall");

		gameobject->AddComponent<HiddenComponent>(trans->GetWorldPosition(), Vec3(0,0,1));
		//gameobject = Instantiate<GameObject>();
		//trans = gameobject->GetComponent<Transform>();
		//trans->SetScale(1, 5, 5);
		//trans->SetPosition(2.5f, 0, 0);
		//draw = gameobject->AddComponent<PNTStaticDraw>();
		//draw->SetMeshResource(L"DEFAULT_CUBE");

		//collision = gameobject->AddComponent<CollisionObb>();
		//collision->SetFixed(true);
		//gameobject->AddTag(L"Wall");

		//gameobject = Instantiate<GameObject>();
		//trans = gameobject->GetComponent<Transform>();
		//trans->SetScale(5, 5, 1);
		//trans->SetPosition(0, 0, 2.5f);
		//draw = gameobject->AddComponent<PNTStaticDraw>();
		//draw->SetMeshResource(L"DEFAULT_CUBE");

		//collision = gameobject->AddComponent<CollisionObb>();
		//collision->SetFixed(true);
		//gameobject->AddTag(L"Wall");

		//gameobject = Instantiate<GameObject>();
		//trans = gameobject->GetComponent<Transform>();
		//trans->SetScale(5, 5, 1);
		//trans->SetPosition(0, 0, -2.5f);
		//draw = gameobject->AddComponent<PNTStaticDraw>();
		//draw->SetMeshResource(L"DEFAULT_CUBE");

		//collision = gameobject->AddComponent<CollisionObb>();
		//collision->SetFixed(true);
		//gameobject->AddTag(L"Wall");

		itbs::Input::CursorSetting::SetIsLock(true);
		itbs::Input::CursorSetting::SetIsDraw(false);

		auto karipos = Vec3();
		for (int i = 0; i < 1; i++)
		{
			auto particle = Instantiate<GameObject>();

			particle->AddComponent<ParticleSystem>();
			particle->GetComponent<Transform>()->SetPosition(karipos);

			karipos.x += 1;
		}
	}
}