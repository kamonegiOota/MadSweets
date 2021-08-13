#pragma once
#include"HiddenComponent.h"
#include"PlayerMover.h"
#include"PlayerCameraMover.h"
#include"SpringArmComponent.h"

namespace basecross
{
	class PlayerHideManager : public Component, public I_HideComponent
	{
		bool m_isHide = false;

		ex_weak_ptr<PlayerMover> m_playerMover;
		ex_weak_ptr<PlayerCameraMover> m_playerCameraMover;
		ex_weak_ptr<Collision> m_collision;

		ex_weak_ptr<SpringArmComponent> m_springArm;

	public:
		PlayerHideManager(std::shared_ptr<GameObject>& owner,std::shared_ptr<PlayerCameraMover>& playerCameraMover);

		void OnStart() override;

		void OnUpdate() override;

		void OnHide(const HideData& hideData) override;

		void OnEndHide(const HideData& hideData) override;
	};
}