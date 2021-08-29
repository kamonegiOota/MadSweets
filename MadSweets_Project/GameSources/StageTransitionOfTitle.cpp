#include"StageTransitionOfTitle.h"
#include"Scene.h"

namespace basecross
{
	StageTransitionOfTitle::StageTransitionOfTitle(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void StageTransitionOfTitle::GoGameStage()
	{
	}

	void StageTransitionOfTitle::GoOptionStage()
	{
		EventSystem::GetInstance(GetStage())->SetUpdateActive(false);

		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToOptionStage");
	}

}