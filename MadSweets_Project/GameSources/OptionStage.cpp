#include"OptionStage.h"
#include"MenuButtonObject.h"
#include"OptionMenuEventer.h"
#include"OptionMainMenuButtonEventer.h"
#include"GaugeLinkedButtonObject.h"
#include"GameSaveManager.h"
#include"SoundHelper.h"
#include"GaugeLinkedButtonOperator.h"

namespace basecross
{
	OptionStage::OptionStage() : Stage() {}

	std::shared_ptr<UIObject> OptionStage::CreateSoundManageMenuObject(const Vec2& position)
	{
		auto& soundSetting = GameSaveManager::GetSoundSetting();

		auto soundManageMenu = Instantiate<UIObject>(Vec3(position.x, position.y, 0), Quat::Identity());

		auto gaugeLinkedButtonObject = Instantiate<GaugeLinkedButtonObject>(Vec3(0, 150, 0), Quat::Identity(), soundManageMenu);
		auto bgmVolumeButton = gaugeLinkedButtonObject->GetComponent<Button>();
		bgmVolumeButton->SetAllButtonImage(L"OptionBGMVolume_TX");
		auto rectTransform = gaugeLinkedButtonObject->GetComponent<RectTransform>();
		rectTransform->SetRectSize(250, 100);
		rectTransform->SetScale(0.75f, 0.75f);
		auto gaugeOperator = gaugeLinkedButtonObject->GetComponent<GaugeLinkedButtonOperator>();
		gaugeOperator->SetGaugeValume(soundSetting->GetBGMVolume());
		gaugeOperator->gaugeUpdateEvent.AddFunc(soundSetting, &SoundSetting::SetBGMVolume);

		gaugeLinkedButtonObject = Instantiate<GaugeLinkedButtonObject>(Vec3(0, 0, 0), Quat::Identity(), soundManageMenu);
		auto seVolumeButton = gaugeLinkedButtonObject->GetComponent<Button>();
		seVolumeButton->SetAllButtonImage(L"OptionSEVolume_TX");
		rectTransform = gaugeLinkedButtonObject->GetComponent<RectTransform>();
		rectTransform->SetRectSize(200, 100);
		rectTransform->SetScale(0.75f, 0.75f);
		gaugeOperator = gaugeLinkedButtonObject->GetComponent<GaugeLinkedButtonOperator>();
		gaugeOperator->SetGaugeValume(soundSetting->GetSEVolume());
		gaugeOperator->gaugeUpdateEvent.AddFunc(soundSetting, &SoundSetting::SetSEVolume);

		
		auto buttonObject = Instantiate<MenuButtonObject>(Vec3(0, -175, 0), Quat::Identity(), soundManageMenu);
		auto subBackButton = buttonObject->GetComponent<Button>();
		subBackButton->SetAllButtonImage(L"MenuBack_TX");
		rectTransform = buttonObject->GetComponent<RectTransform>();
		rectTransform->SetRectSize(200, 100);
		rectTransform->SetScale(0.75f, 0.75f);

		bgmVolumeButton->SetVerticalNextSelectable(seVolumeButton);
		seVolumeButton->SetVerticalBeforeSelectable(bgmVolumeButton);
		seVolumeButton->SetVerticalNextSelectable(subBackButton);
		subBackButton->SetVerticalBeforeSelectable(seVolumeButton);

		subBackButton->pushEvent.AddFunc(EventSystem::GetInstance(GetThis<OptionStage>()).GetShard(), &EventSystem::PopSelectable);

		return soundManageMenu;
	}

	void OptionStage::OptionSaveLoad()
	{
		auto& soundSetting = GameSaveManager::GetSoundSetting();

		int i = 0;
	}

	void OptionStage::OnCreate()
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

		OptionSaveLoad();

		float mainToSubLength = 100.0f;

		auto soundManageMenu = CreateSoundManageMenuObject(Vec2(mainToSubLength, 0));

		auto mainOptionMenuObject = Instantiate<UIObject>(Vec3(-500,0,0),Quat::Identity());

		auto buttonObject = Instantiate<MenuButtonObject>(Vec3(0, 100, 0), Quat::Identity(), mainOptionMenuObject);
		auto soundManageButton = buttonObject->GetComponent<Button>();
		soundManageButton->SetAllButtonImage(L"MenuSoundManage_TX");
		auto rectTransform = buttonObject->GetComponent<RectTransform>();
		rectTransform->SetRectSize(250, 100);
		auto mainMenuButtonEventer = buttonObject->AddComponent<OptionMainMenuButtonEventer>(soundManageMenu);
		soundManageButton->selectEvent.AddFunc(mainMenuButtonEventer, &OptionMainMenuButtonEventer::OnSelect);
		soundManageButton->pushEvent.AddFunc(mainMenuButtonEventer, &OptionMainMenuButtonEventer::OnPush);
		soundManageButton->outSelectEvent.AddFunc(mainMenuButtonEventer, &OptionMainMenuButtonEventer::OnoutSelect);
		
		buttonObject = Instantiate<MenuButtonObject>(Vec3(0, -100, 0), Quat::Identity(), mainOptionMenuObject);
		auto backButton = buttonObject->GetComponent<Button>();
		backButton->SetAllButtonImage(L"MenuBack_TX");
		rectTransform = buttonObject->GetComponent<RectTransform>();
		rectTransform->SetRectSize(200, 100);

		auto gameobject = Instantiate<GameObject>();
		auto eventer = gameobject->AddComponent<OptionMenuEventer>();
		
		backButton->pushEvent.AddFunc(eventer, &OptionMenuEventer::GoTitleStage);

		soundManageButton->SetVerticalNextSelectable(backButton);
		backButton->SetVerticalBeforeSelectable(soundManageButton);

		EventSystem::GetInstance(GetThis<Stage>())->SetNowSelectable(soundManageButton);
	}
}