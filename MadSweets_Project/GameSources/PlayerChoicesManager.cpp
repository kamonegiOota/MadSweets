#include"PlayerChoicesManager.h"
#include"ChoicesComponentBase.h"
#include"PlayerInputer.h"

namespace basecross
{
	PlayerChoicesManager::PlayerChoicesManager(std::shared_ptr<GameObject>& owner,const std::shared_ptr<GameObject>& cameraObject) :
		Component(owner),
		m_playerCameraObject(cameraObject),
		m_searchRange(2.0f)
	{

	}

	void PlayerChoicesManager::SetSearchRange(const float searchRange)
	{
		m_searchRange = searchRange;
	}

	float PlayerChoicesManager::GetSearchRange() const
	{
		return m_searchRange;
	}

	void PlayerChoicesManager::OnStart()
	{
		m_playerChoicesList = GetStage()->GetSharedGameObject<GameObject>(L"PlayerChoicesList")->GetComponent<ChoicesList>();
	}

	void PlayerChoicesManager::OnUpdate()
	{
		auto startPosition = m_playerCameraObject->GetComponent<Transform>()->GetWorldPosition();
		auto searchEndPosition = startPosition + m_playerCameraObject->GetComponent<Transform>()->GetForword() * m_searchRange;

		for (auto& object : GetStage()->GetGameObjectVec())
		{
			auto choicesComponent = object->GetComponent<ChoicesComponentBase>(false);

			if (!choicesComponent)
			{
				continue;
			}

			auto collision = object->GetComponent<Collision>(false);

			if (!collision)
			{
				continue;
			}

			auto it = std::find(m_rayCollisionObjects.begin(), m_rayCollisionObjects.end(), collision->GetGameObject());

			if (collision->IsRayHit(startPosition, searchEndPosition))
			{
				if (it == m_rayCollisionObjects.end())
				{
					m_rayCollisionObjects.push_back(collision->GetGameObject());

					m_playerChoicesList->AddChoice(choicesComponent->GetChoicesObjectAndEvent(GetGameObject()));
				}
			}
			else
			{
				if (it != m_rayCollisionObjects.end())
				{
					m_rayCollisionObjects.erase(it);
					m_playerChoicesList->RemoveChoice(collision->GetGameObject());
				}
			}
		}

		if (PlayerInputer::IsDecision())
		{
			m_playerChoicesList->Invoke();
		}

	}
}