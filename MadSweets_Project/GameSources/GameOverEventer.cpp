#include"GameOverEventer.h"

namespace basecross
{
	GameOverEventer::GameOverEventer(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void GameOverEventer::OnRetry()
	{
		EventSystem::GetInstance(GetStage())->SetUpdateActive(false);
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<SceneBase>(), L"ToMargeTestStage");
	}

	void GameOverEventer::OnBackTitle()
	{
		EventSystem::GetInstance(GetStage())->SetUpdateActive(false);
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<SceneBase>(), L"ToTitleStage");
	}
}