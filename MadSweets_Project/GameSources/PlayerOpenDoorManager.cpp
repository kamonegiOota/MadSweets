#include"PlayerOpenDoorManager.h"

namespace basecross
{
	PlayerOpenDoorManager::PlayerOpenDoorManager(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void PlayerOpenDoorManager::MessageWindowFinish()
	{
		GetGameObject()->SetUpdateActive(true);
		m_messageWindowObject->SetActive(false);
		m_isOneFlameSkip = true;
	}

	void PlayerOpenDoorManager::OnStart()
	{
		m_gameItemGetter = GetGameObject()->GetComponent<PlayerGameItemGetter>();

		m_messageWindowObject = GetStage()->GetSharedGameObject<GameMessageWindowObject>(GameMessageWindowObject::SHARED_KEY);

		m_messageWindow = m_messageWindowObject->GetComponent<MessageWindow>();

		m_messageWindowObject->SetActive(false);

		m_mover = GetGameObject()->GetComponent<PlayerMover>();

		m_messageWindow->finishPushEvent.AddFunc(GetThis<PlayerOpenDoorManager>(), &PlayerOpenDoorManager::MessageWindowFinish);
	}

	void PlayerOpenDoorManager::OnEvent()
	{
		if (m_isOneFlameSkip)
		{
			m_isOneFlameSkip = false;
			return;
		}

		if (!GetGameObject()->GetUpdateActive())
		{
			return;
		}

		if (m_gameItemGetter->FindGameItem(m_findGameItem))
		{
			MessageBox(0, L"Œ®‚ªŠJ‚«‚Ü‚µ‚½", L"", 0);
		}
		else
		{
			m_messageWindowObject->SetActive(true);
			m_messageWindow->SetMessageText(L"‚©‚¬‚ªŠ|‚©‚Á‚Ä‚¢‚Ü‚·");
			m_messageWindow->PlayMessage();
			EventSystem::GetInstance(GetStage())->PushSelectable(m_messageWindow.GetShard());
			GetGameObject()->SetUpdateActive(false);
		}
	}
}