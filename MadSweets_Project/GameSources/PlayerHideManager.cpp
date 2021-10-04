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

		m_playerChoicesManager = GetGameObject()->GetComponent<PlayerChoicesManager>();

		m_unHideObject = GetStage()->Instantiate<GameObject>();

		m_playerAnimator = GetGameObject()->GetComponent<Animator<PlayerAnimationMember, PlayerState>>();
	}

	void PlayerHideManager::OnUpdate()
	{
	}

	void PlayerHideManager::OnHide(HideData& hideData)
	{
		m_playerMover->SetUpdateActive(false);
		m_playerAnimator->SetAnimationSpeed(0.0f);

		transform->SetWorldPosition(hideData.hideWorldPosition);
		transform->SetForward(hideData.hideForward);

		m_playerRotater->Restrict(XM_PIDIV4);

		m_collision->SetAfterCollision(AfterCollision::None);

		SimpleSoundManager::OnePlaySE(L"HideSE",0.01f);

		m_choice = std::make_shared<ChoicesObjectAndEvent>(L"o‚é", m_unHideObject, [&hideData, this]() {OnEndHide(hideData); });
		m_playerChoicesManager->AddPlayerChoice(m_choice);

		hideData.hideObject = GetGameObject();
	}

	void PlayerHideManager::OnEndHide(HideData& hideData)
	{
		m_playerMover->SetUpdateActive(true);
		m_playerAnimator->SetAnimationSpeed(1.0f);
		auto worldPosition = transform->GetWorldPosition();
		transform->SetWorldPosition(worldPosition + hideData.hideForward);

		m_playerRotater->UnRestrict();

		m_collision->SetAfterCollision(AfterCollision::Auto);

		m_playerChoicesManager->RemovePlayerChoice(m_unHideObject);

		hideData.hideObject = nullptr;
	}
}