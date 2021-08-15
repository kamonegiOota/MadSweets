#pragma once
#include"HiddenComponent.h"
#include"PlayerMover.h"
#include"PlayerRotater.h"

namespace basecross
{
	class PlayerHideManager : public Component, public I_HideComponent
	{
		bool m_isHide = false;

		ex_weak_ptr<PlayerMover> m_playerMover;
		ex_weak_ptr<PlayerRotater> m_playerRotater;
		ex_weak_ptr<Collision> m_collision;

	public:
		PlayerHideManager(std::shared_ptr<GameObject>& owner);

		void OnStart() override;

		void OnUpdate() override;

		void OnHide(const HideData& hideData) override;

		void OnEndHide(const HideData& hideData) override;
	};
}