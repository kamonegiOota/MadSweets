#include"ClearStage.h"
#include"GameMessageWindowObject.h"
#include"MessageWindow.h"
#include"AlphaFadeCtrl.h"
#include"PlayerInputer.h"

namespace basecross
{
	ClearStage::ClearStage() : Stage() {}

	void ClearStage::FadeInEnd()
	{
		EventSystem::GetInstance(GetThis<Stage>())->PushSelectable(m_messageWindow.GetShard());
		m_messageWindow->PlayMessage();
		
	}

	void ClearStage::FadeOutEnd()
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<SceneBase>(), L"ToTitleStage");
	}

	void ClearStage::OnCreate()
	{
		const Vec3 eye(0.0f, +15.0f, -30.0f);
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
		//PtrMultiLight->SetAmbientLightColor(Col4(1.0f,0.1f,0.1f,0.1f));

		Vec3 poss[] = {
			{Vec3(0.0f,0.5f,0.0f)},
			{Vec3(0.0f,-0.5f,0.0f)},
			{Vec3(-0.5f,0.0f,0.0f)},
		};

		//ライトの設定
		for (int i = 0; i < 3; i++) {
			auto& light = PtrMultiLight->GetLight(i);
			light.m_DiffuseColor = Col4(0.35f);
			//light.m_Directional = Vec3(0.0f);
			light.m_SpecularColor = Col4(0.35f);
			//light.m_Directional = poss[i];
		}

		auto imageObject = Instantiate<UIObject>();
		imageObject->SetDrawLayer(-100);
		auto rectTransform = imageObject->GetComponent<RectTransform>();
		rectTransform->SetRectSize(1280, 800);
		auto image = imageObject->AddComponent<Image>();

		image->SetTextureResource(L"FadeBack_Tx");
		image->SetDiffuse(Col4(0.25f, 0.25f, 0.25f, 1.0f));

		auto messageWindowObject = Instantiate<GameMessageWindowObject>();
		messageWindowObject->SetDrawLayer(0);
		messageWindowObject->GetComponent<RectTransform>()->SetPosition(0, 0);
		m_messageWindow = messageWindowObject->GetComponent<MessageWindow>();

		std::wstring messageText =
			L"このうえは、おかしのいえ。おいしいおかしがたくさんあるの！\n"
			L"でも、おかしのいえはもどっちゃった。\n"
			L"もし、これを読んだら、長さは短いけどいつも5本ずつおかれていた××××と、\n"
			L"ふしぎなもようの入ったまん丸の××××××には気をつけて。\n"
			L"それはきっと××の××から×××れた\n"
			L"ぼくは、またそれをたべるために、××をさ";

		m_messageWindow->SetMessageText(messageText);

		auto alphaFade = Instantiate<UIObject>()->AddComponent<AlphaFadeCtrl>();
		alphaFade->SetSpeed(2.0f);
		alphaFade->AddEndAction(GetThis<ClearStage>(), &ClearStage::FadeInEnd);
		alphaFade->FadeInStart();

		auto uiobject = Instantiate<UIObject>();
		uiobject->SetDrawLayer(1000);
		alphaFade = uiobject->AddComponent<AlphaFadeCtrl>();
		alphaFade->SetSpeed(2.0f);
		alphaFade->AddEndAction(GetThis<ClearStage>(), &ClearStage::FadeOutEnd);

		m_messageWindow->finishPushEvent.AddFunc(alphaFade, &AlphaFadeCtrl::FadeOutStart);

		EventSystem::GetInstance(GetThis<Stage>())->SetBasicInputer(PlayerInputer::GetInstance());
	}
}