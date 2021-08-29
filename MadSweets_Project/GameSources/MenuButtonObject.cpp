#include"MenuButtonObject.h"
#include"UIHelper.h"
#include"MenuButtonSounder.h"
#include"MenuButtonEventer.h"

namespace basecross
{
	MenuButtonObject::MenuButtonObject(std::shared_ptr<Stage>& stage) :
		UIObject(stage)
	{

	}

	void MenuButtonObject::OnCreate()
	{
		auto button = AddComponent<Button>();
		
		auto sounder = AddComponent<MenuButtonSounder>();

		auto eventer = AddComponent<MenuButtonEventer>();

		sounder->SetOutSelectSoundKey(L"UI_SelectSE");

		sounder->SetPushSoundKey(L"UI_PushSE");

		button->selectEvent.AddFunc(eventer, &MenuButtonEventer::OnSelectSetDiffuse);

		button->pushEvent.AddFunc(sounder, &MenuButtonSounder::OnPushSoundPlay);

		button->outSelectEvent.AddFunc(eventer, &MenuButtonEventer::OnOutSelectSetDiffuse);
		button->outSelectEvent.AddFunc(sounder, &MenuButtonSounder::OnOutSelectSoundPlay);

	}
}