#include"PlayerHideManager.h"

namespace basecross
{
	PlayerHideManager::PlayerHideManager(std::shared_ptr<GameObject>& owner,std::shared_ptr<PlayerCameraMover>& playerCameraMover) :
		Component(owner),
		m_playerCameraMover(playerCameraMover)
	{
		m_springArm = m_playerCameraMover->GetGameObject()->GetComponent<SpringArmComponent>();
	}

	void PlayerHideManager::OnStart()
	{
		m_playerMover = GetGameObject()->GetComponent<PlayerMover>();

		m_collision = GetGameObject()->GetComponent<Collision>();
	}

	void PlayerHideManager::OnUpdate()
	{
	}

	void PlayerHideManager::OnHide(const HideData& hideData)
	{
		m_playerMover->SetUpdateActive(false);
		m_playerCameraMover->SetUpdateActive(false);

		m_playerCameraMover->SetForward(-hideData.hideForward);

		m_springArm->SetArmRange(0);


		transform->SetWorldPosition(hideData.hideWorldPosition);
		transform->SetForward(hideData.hideForward);

		m_collision->SetAfterCollision(AfterCollision::None);
	}

	void PlayerHideManager::OnEndHide(const HideData& hideData)
	{
		m_playerMover->SetUpdateActive(true);
		m_playerCameraMover->SetUpdateActive(true);

		m_springArm->SetArmRange(10);

		auto worldPosition = transform->GetWorldPosition();
		transform->SetWorldPosition(worldPosition + hideData.hideForward);

		m_collision->SetAfterCollision(AfterCollision::Auto);
	}
}