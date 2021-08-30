#include"ItabashiStage.h"
#include"PlayerObject.h"
#include"GaugeUI.h"
#include"TestEatenObject.h"
#include"FontHelper.h"
#include"SoundHelper.h"
#include"HiddenComponent.h"
#include"ParticleSystem.h"
#include"GaugeManager.h"
#include"CameraHelper.h"
#include"MenuButtonObject.h"
#include"StageTransitionOfTitle.h"
#include"MessageWindow.h"

namespace basecross
{
	class TEST
	{
	public:
		static void test()
		{
			SimpleSoundManager::OnePlaySE(L"UI_SelectSE");
		}
	};

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

		auto cameraobj = Instantiate<CameraObject>();
		auto brain = cameraobj->GetComponent<CameraBrain>();
		brain->SetCameraBlend(std::make_shared<CameraBlendLinear>(1));

		auto gauge = Instantiate<GaugeUI>();
		auto gaugeManager = gauge->GetComponent<GaugeManager>();

		gaugeManager->SetGaugeImage(L"Tx_Cake");
		gaugeManager->SetGaugeRectSize(160, 160);
		gaugeManager->SetGaugeFillType(ImageFillType::Vertical);

		auto rectTransform = gauge->GetComponent<RectTransform>();
		rectTransform->SetPosition(-500, -500);
		//rectTransform->SetAnchor(AnchorType::LeftUp);

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

		SimpleSoundManager::ChangeBGM(L"TitleBGM2", 1.0f);

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

		std::wstring  message =
			L"さあ、憐んで、血統書　持ち寄って反教典\n沈んだ唱導　腹這幻聴　謁見　席巻　妄信症\n踊れ酔え孕め　アヴァターラ新大系\n斜めの幻聴　錻力と宗教　ラル・ラリ・唱えろ生";

		auto messageWindowObject = Instantiate<MessageWindowObject>();
		auto messageWindow = messageWindowObject->GetComponent<MessageWindow>();
		messageWindow->SetMessageText(message);
		messageWindow->PlayMessage();
		messageWindow->SetOneSecondDisplayedCharNum(10);
		messageWindow->finishPushEvent.AddFunc(&TEST::test);
		rectTransform = messageWindowObject->GetComponent<RectTransform>();
		rectTransform->SetRectSize(1000, 200);
		auto textBox = messageWindowObject->GetComponent<TextBox>();
		//textBox->SetText(L"こんにちは");
		textBox->SetFontColor(Col4(1.0f));
		textBox->SetFontSize(50);
		textBox->SetBoxColor(Col4(0.0f, 0.0f, 0.0f, 1.0f));
		textBox->SetTextVerticalAlignment(TextBox::TextVerticalAlignment::Center);

		EventSystem::GetInstance(GetThis<ItabashiStage>())->SetNowSelectable(messageWindow);
	}
}