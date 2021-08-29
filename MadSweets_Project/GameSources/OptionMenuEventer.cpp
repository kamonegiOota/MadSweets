#include"OptionMenuEventer.h"
#include"Scene.h"
#include"GameSaveManager.h"
#include"SoundHelper.h"

namespace basecross
{
	OptionMenuEventer::OptionMenuEventer(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void OptionMenuEventer::OnFadeOut()
	{
		EventSystem::GetInstance(GetStage())->SetUpdateActive(false);
	}

	void OptionMenuEventer::GoTitleStage()
	{
		GameSaveManager::GetSoundSetting()->Save();
		PostEvent(0.0f, GetThis<Component>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
	}

	void OptionMenuEventer::OnBackMainOptionMenu()
	{
		EventSystem::GetInstance(GetStage())->PopSelectable();
	}

	void OptionMenuEventer::OnUpdate()
	{
	}
}