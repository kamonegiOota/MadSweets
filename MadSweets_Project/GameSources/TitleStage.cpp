/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include "TitleStage.h"

#include "MTestEnemyObject.h"
#include "DebugObject.h"

#include "UIHelper.h"
#include "TitleNameCtrl.h"
#include "TitleNameObject.h"
#include "TitleFadeCtrl.h"
#include "AlphaFadeCtrl.h"
#include "FadeChocoCtrl.h"
#include "EventSprite.h"
#include "MyUtility.h"

#include "PlayerInputer.h"

// 板橋 追加分 --------------------------
#include "SoundHelper.h"

#include "MenuButtonObject.h"
#include "StageTransitionOfTitle.h"

#include "PlayerInputer.h"

// --------------------------------------

//#include "AlphaFadeObject.h"
//#include "AlphaFadeCtrl.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -15.0f);
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
	}

	void TitleStage::CreateTitle() {
		//タイトルの画像の表示
		auto title  = Instantiate<TitleNameObject>();
		title->GetComponent<RectTransform>()->SetPosition(0, 200);
	}

	void TitleStage::CreateFadeCtrl(std::shared_ptr<Button>& startButton, std::shared_ptr<Button>& goOptionButton) {
		//TitleFadeCtrlを生成
		auto titleFadeObject = Instantiate<UIObject>();
		auto fade = titleFadeObject->AddComponent<TitleFadeCtrl>();

		startButton->pushEvent.AddFunc(fade, &TitleFadeCtrl::FadeStart);

		//チョコフェードの実装
		auto chocoFadeObject = Instantiate<UIObject>(Vec3(), Quat::Identity(), titleFadeObject);
		chocoFadeObject->AddComponent<FadeChocoCtrl>();
		chocoFadeObject->SetDrawLayer(10000);
		

		//イベントスプライトの設定
		vector<wstring> sprites = {
			L"Prologue_Tx",
			L"PrologueScond_Tx",
		};
		Instantiate<UIObject>(Vec3(), Quat::Identity(), titleFadeObject)->AddComponent<EventSprite>(sprites);
		//アルファフェードの実装
		Instantiate<GameObject>(Vec3(), Quat::Identity(), titleFadeObject)->AddComponent<AlphaFadeCtrl>();

		auto alphaFade = Instantiate<GameObject>(Vec3(), Quat::Identity(), titleFadeObject)->AddComponent<AlphaFadeCtrl>();

		alphaFade->AddEndAction(GetThis<TitleStage>(), &TitleStage::GoOption);
		alphaFade->SetSpeed(7.5f);
		goOptionButton->pushEvent.AddFunc(alphaFade, &AlphaFadeCtrl::FadeOutStart);

		alphaFade = Instantiate<GameObject>(Vec3(), Quat::Identity(), titleFadeObject)->AddComponent<AlphaFadeCtrl>();
		alphaFade->SetSpeed(7.5f);
		alphaFade->FadeInStart();
	}

	void TitleStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			if (!SimpleSoundManager::IsPlayingBGM(L"TitleBGM1"))
			{
				SimpleSoundManager::ChangeBGM(L"TitleBGM1");
			}

			auto backGroundObject = Instantiate<UIObject>();
			auto image = backGroundObject->AddComponent<Image>();
			image->SetTextureResource(L"TitleBack_Tx");
			auto rectTransform = backGroundObject->GetComponent<RectTransform>();
			rectTransform->SetRectSize(1280, 800);

			auto stageTransition = Instantiate<GameObject>()->AddComponent<StageTransitionOfTitle>();

			auto titleObject = Instantiate<UIObject>();
			image = titleObject->AddComponent<Image>();
			image->SetTextureResource(L"TitleFont_Tx");
			rectTransform = titleObject->GetComponent<RectTransform>();

			rectTransform->SetRectSize(512, 256);
			rectTransform->SetPosition(0, 200);

			auto menuButtonObject = Instantiate<MenuButtonObject>();
			auto startButton = menuButtonObject->GetComponent<Button>();
			startButton->SetAllButtonImage(L"MenuPressAToStart_TX");
			startButton->pushEvent.AddFunc(stageTransition, &StageTransitionOfTitle::GoGameStage);

			rectTransform = menuButtonObject->GetComponent<RectTransform>();

			rectTransform->SetRectSize(645, 100);
			rectTransform->SetPosition(0, -100);

			menuButtonObject = Instantiate<MenuButtonObject>();
			auto goOptionButton = menuButtonObject->GetComponent<Button>();
			goOptionButton->SetAllButtonImage(L"MenuOption_TX");
			goOptionButton->pushEvent.AddFunc(stageTransition, &StageTransitionOfTitle::GoOptionStage);

			rectTransform = menuButtonObject->GetComponent<RectTransform>();

			rectTransform->SetRectSize(250, 100);
			rectTransform->SetPosition(0, -200);

			startButton->SetVerticalNextSelectable(goOptionButton);
			goOptionButton->SetVerticalBeforeSelectable(startButton);

			EventSystem::GetInstance(GetThis<Stage>())->SetNowSelectable(startButton);

			EventSystem::GetInstance(GetThis<Stage>())->SetBasicInputer(PlayerInputer::GetInstance());

			CreateTitle();
			CreateFadeCtrl(startButton, goOptionButton);

		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate() {
	}

	void TitleStage::GoOption()
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<SceneBase>(), L"ToOptionStage");
	}
}

//endbasecross