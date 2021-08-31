#pragma once
#include"Trigger.h"

namespace basecross
{
	struct PlayerAnimationMember
	{
		Trigger changeStance;
		float moveSpeed;
		bool isDash;
	};

	enum class PlayerState
	{
		StandStay,
		CrouchStay,
		StandToCrouch,
		CrouchToStand,
		StandMove,
		CrouchMove
	};

	class PlayerObject : public GameObject
	{
		void CreateAnimator();
	public:
		PlayerObject(std::shared_ptr<Stage>& stage);

		void OnCreate() override;
		void OnUpdate() override;
	};
}