#include"PlayerHideManager.h"
#include"SoundHelper.h"

namespace basecross
{
	PlayerHideManager::PlayerHideManager(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{
	}

	void PlayerHideManager::OnStart()
	{
		m_playerMover = GetGameObject()->GetComponent<PlayerMover>();

		m_playerRotater = GetGameObject()->GetComponent<PlayerRotater>();

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

		m_playerRotater->Restrict(XM_PIDIV4);

		m_collision->SetAfterCollision(AfterCollision::None);

		SimpleSoundManager::OnePlaySE(L"HideSE",0.01f);
	}

	void PlayerHideManager::OnEndHide(const HideData& hideData)
	{
		m_playerMover->SetUpdateActive(true);

		auto worldPosition = transform->GetWorldPosition();
		transform->SetWorldPosition(worldPosition + hideData.hideForward);

		m_playerRotater->UnRestrict();

		m_collision->SetAfterCollision(AfterCollision::Auto);
	}
}