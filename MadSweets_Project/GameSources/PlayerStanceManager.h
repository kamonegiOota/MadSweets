#pragma once
#include"PlayerObject.h"
#include"AnimationHelper.h"

namespace basecross
{
	class PlayerStanceManager : public Component
	{
		ex_weak_ptr<Animator<PlayerAnimationMember, PlayerState>> m_animator;

		void PlayerStanceChange();
	public:
		PlayerStanceManager(std::shared_ptr<GameObject>& owner);

		void OnCreate() override;

		void OnUpdate() override;
	};
}