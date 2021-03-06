#pragma once
#include"HiddenComponent.h"
#include"PlayerMover.h"
#include"PlayerRotater.h"
#include "PlayerChoicesManager.h"
#include "PlayerObject.h"

namespace basecross
{
	class PlayerHideManager : public Component, public I_HideComponent
	{
		bool m_isHide = false;

		std::shared_ptr<GameObject> m_unHideObject;

		ex_weak_ptr<PlayerMover> m_playerMover;
		ex_weak_ptr<PlayerRotater> m_playerRotater;
		ex_weak_ptr<Collision> m_collision;

		ex_weak_ptr<PlayerChoicesManager> m_playerChoicesManager;
		ex_weak_ptr<Animator<PlayerAnimationMember, PlayerState>> m_playerAnimator;

		std::shared_ptr<ChoicesObjectAndEvent> m_choice;

	public:
		PlayerHideManager(std::shared_ptr<GameObject>& owner);

		void OnStart() override;

		void OnUpdate() override;

		void OnHide(HideData& hideData) override;

		void OnEndHide(HideData& hideData) override;
	};
}