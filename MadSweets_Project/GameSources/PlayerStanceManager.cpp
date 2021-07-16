#include"PlayerStanceManager.h"
#include"PlayerInputer.h"

namespace basecross
{
	PlayerStanceManager::PlayerStanceManager(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void PlayerStanceManager::PlayerStanceChange()
	{
		if (PlayerInputer::IsChangeStance())
		{
			if (m_playerStance == PlayerStance::Stand)
			{
				m_playerStance = PlayerStance::Crouch;
				return;
			}

			if (m_playerStance == PlayerStance::Crouch)
			{
				m_playerStance = PlayerStance::Stand;
				return;
			}
		}
	}

	PlayerStance PlayerStanceManager::GetPlayerStance() const
	{
		return m_playerStance;
	}

	void PlayerStanceManager::OnCreate()
	{

	}

	void PlayerStanceManager::OnUpdate()
	{
		PlayerStanceChange();
	}
}