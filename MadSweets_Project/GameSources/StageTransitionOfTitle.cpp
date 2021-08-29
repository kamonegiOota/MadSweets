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
		EventSystem::GetInstance(GetStage())->SetUpdateActive(false);
	}

	void StageTransitionOfTitle::GoOptionStage()
	{
		EventSystem::GetInstance(GetStage())->SetUpdateActive(false);
	}

}