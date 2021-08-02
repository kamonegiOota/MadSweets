#include"PlayerHideManager.h"

namespace basecross
{
	PlayerHideManager::PlayerHideManager(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

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

		transform->SetWorldPosition(hideData.hideWorldPosition);
		transform->SetForward(hideData.hideForward);

		m_collision->SetAfterCollision(AfterCollision::None);
	}

	void PlayerHideManager::OnEndHide(const HideData& hideData)
	{
		m_playerMover->SetUpdateActive(true);

		auto worldPosition = transform->GetWorldPosition();
		transform->SetWorldPosition(worldPosition + hideData.hideForward);

		m_collision->SetAfterCollision(AfterCollision::Auto);
	}
}