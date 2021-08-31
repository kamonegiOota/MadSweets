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
		//ƒrƒ…[‚ÌƒJƒƒ‰‚Ìİ’è
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//ƒ}ƒ‹ƒ`ƒ‰ƒCƒg‚Ìì¬
		auto PtrMultiLight = CreateLight<MultiLight>();

		//ƒfƒtƒHƒ‹ƒg‚Ìƒ‰ƒCƒeƒBƒ“ƒO‚ğw’è
		PtrMultiLight->SetDefaultLighting();
		//PtrMultiLight->SetAmbientLightColor(Col4(1.0f,0.1f,0.1f,0.1f));

		Vec3 poss[] = {
			{Vec3(0.0f,0.5f,0.0f)},
			{Vec3(0.0f,-0.5f,0.0f)},
			{Vec3(-0.5f,0.0f,0.0f)},
		};

		//ƒ‰ƒCƒg‚Ìİ’è
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
			L"‚±‚Ì‚¤‚¦‚ÍA‚¨‚©‚µ‚Ì‚¢‚¦B‚¨‚¢‚µ‚¢‚¨‚©‚µ‚ª‚½‚­‚³‚ñ‚ ‚é‚ÌI\n"
			L"‚Å‚àA‚¨‚©‚µ‚Ì‚¢‚¦‚Í‚à‚Ç‚Á‚¿‚á‚Á‚½B\n"
			L"‚à‚µA‚±‚ê‚ğ“Ç‚ñ‚¾‚çA’·‚³‚Í’Z‚¢‚¯‚Ç‚¢‚Â‚à5–{‚¸‚Â‚¨‚©‚ê‚Ä‚¢‚½~~~~‚ÆA\n"
			L"‚Ó‚µ‚¬‚È‚à‚æ‚¤‚Ì“ü‚Á‚½‚Ü‚ñŠÛ‚Ì~~~~~~‚É‚Í‹C‚ğ‚Â‚¯‚ÄB\n"
			L"‚»‚ê‚Í‚«‚Á‚Æ~~‚Ì~~‚©‚ç~~~‚ê‚½\n"
			L"‚Ú‚­‚ÍA‚Ü‚½‚»‚ê‚ğ‚½‚×‚é‚½‚ß‚ÉA~~‚ğ‚³";

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