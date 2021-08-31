#include"GameOverStage.h"
#include"MenuButtonObject.h"
#include"GameOverEventer.h"
#include"AlphaFadeCtrl.h"
#include"PlayerInputer.h"
#include"SoundHelper.h"

namespace basecross
{
	GameOverStage::GameOverStage() : Stage() {}

	void GameOverStage::OnCreate()
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

		SimpleSoundManager::ChangeBGM(L"GameOverBGM");

		auto backGroundObject = Instantiate<UIObject>();
		auto backGroundImage = backGroundObject->AddComponent<Image>();
		backGroundImage->SetTextureResource(L"GameOverBackGround_TX");
		auto rectTransform = backGroundObject->GetComponent<RectTransform>();
		rectTransform->SetRectSize(1280, 800);

		auto eventer = Instantiate<GameObject>()->AddComponent<GameOverEventer>();

		const int drawLayer = 10;
		auto gameOverObject = Instantiate<UIObject>();
		gameOverObject->SetDrawLayer(drawLayer);
		auto gameOverImage = gameOverObject->AddComponent<Image>();
		gameOverImage->SetTextureResource(L"GameOverImage_TX");
		rectTransform = gameOverObject->GetComponent<RectTransform>();
		rectTransform->SetRectSize(730, 195);
		rectTransform->SetPosition(0, 200);

		auto menuButtonObject = Instantiate<MenuButtonObject>();

		auto retryButton = menuButtonObject->GetComponent<Button>();
		retryButton->SetAllButtonImage(L"Retry_TX");
		retryButton->pushEvent.AddFunc(eventer, &GameOverEventer::OnRetry);

		rectTransform = menuButtonObject->GetComponent<RectTransform>();
		rectTransform->SetRectSize(295, 80);
		rectTransform->SetPosition(0, -150);

		menuButtonObject = Instantiate<MenuButtonObject>();

		auto backTitleButton = menuButtonObject->GetComponent<Button>();
		backTitleButton->SetAllButtonImage(L"BackTitle_TX");
		backTitleButton->pushEvent.AddFunc(eventer, &GameOverEventer::OnBackTitle);

		rectTransform = menuButtonObject->GetComponent<RectTransform>();
		rectTransform->SetRectSize(580, 80);
		rectTransform->SetPosition(0, -250);

		retryButton->SetVerticalNextSelectable(backTitleButton);
		backTitleButton->SetVerticalBeforeSelectable(retryButton);

		auto alphaFade = Instantiate<UIObject>()->AddComponent<AlphaFadeCtrl>();
		alphaFade->SetSpeed(7.5f);
		alphaFade->FadeInStart();

		alphaFade = Instantiate<UIObject>()->AddComponent<AlphaFadeCtrl>();
		alphaFade->SetSpeed(7.5f);

		alphaFade->AddEndAction(eventer, &GameOverEventer::OnRetry);

		retryButton->pushEvent.AddFunc(eventer, &GameOverEventer::OnFadeOut);
		retryButton->pushEvent.AddFunc(alphaFade, &AlphaFadeCtrl::FadeOutStart);

		alphaFade = Instantiate<UIObject>()->AddComponent<AlphaFadeCtrl>();
		alphaFade->SetSpeed(7.5f);

		alphaFade->AddEndAction(eventer, &GameOverEventer::OnBackTitle);

		backTitleButton->pushEvent.AddFunc(eventer, &GameOverEventer::OnFadeOut);
		backTitleButton->pushEvent.AddFunc(alphaFade, &AlphaFadeCtrl::FadeOutStart);



		EventSystem::GetInstance(GetThis<GameOverStage>())->SetNowSelectable(retryButton);
		EventSystem::GetInstance(GetThis<Stage>())->SetBasicInputer(PlayerInputer::GetInstance());
	}
}