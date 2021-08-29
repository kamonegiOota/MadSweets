#pragma once

namespace basecross
{
	class StageTransitionOfTitle : public Component
	{
	public:
		StageTransitionOfTitle(std::shared_ptr<GameObject>& owner);

		void GoGameStage();

		void GoOptionStage();
	};
}