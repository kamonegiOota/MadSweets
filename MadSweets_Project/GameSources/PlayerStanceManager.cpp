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
			auto nowState = m_animator->GetNowState();
			if (nowState == PlayerState::StandStay || nowState == PlayerState::CrouchStay)
			{
				m_animator->GetMemberRefarence().changeStance.Fire();

			}
		}
	}

	void PlayerStanceManager::OnCreate()
	{
		m_animator = GetGameObject()->GetComponent<Animator<PlayerAnimationMember, PlayerState>>();
	}

	void PlayerStanceManager::OnUpdate()
	{
		PlayerStanceChange();
	}
}