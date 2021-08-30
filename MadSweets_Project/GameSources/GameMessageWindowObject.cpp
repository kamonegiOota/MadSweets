#include"GameMessageWindowObject.h"
#include"MessageWindow.h"

namespace basecross
{
	const std::wstring GameMessageWindowObject::SHARED_KEY = L"GameMessageWindowObject";

	GameMessageWindowObject::GameMessageWindowObject(std::shared_ptr<Stage>& stage) :
		UIObject(stage)
	{

	}

	void GameMessageWindowObject::OnCreate()
	{
		SetDrawLayer(10000);

		auto rectTransform = GetComponent<RectTransform>();

		rectTransform->SetRectSize(600, 160);
		rectTransform->SetPosition(0, -200);

		auto textBox = AddComponent<TextBox>();
		textBox->SetBoxColor(Col4(0.0f, 0.0f, 0.0f, 1.0f));
		textBox->SetFontColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		textBox->SetTextVerticalAlignment(TextBox::TextVerticalAlignment::Center);
		textBox->SetFontSize(25);
		auto messageBox = AddComponent<MessageWindow>();
		messageBox->SetOneSecondDisplayedCharNum(30);
		messageBox->finishPushEvent.AddFunc(EventSystem::GetInstance(GetStage()).GetShard(), &EventSystem::PopSelectable);

		GetStage()->SetSharedGameObject(SHARED_KEY, GetThis<GameObject>());
	}
}