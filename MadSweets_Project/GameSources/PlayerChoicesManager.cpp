#include"PlayerChoicesManager.h"
#include"ChoicesComponentBase.h"
#include"PlayerInputer.h"

namespace basecross
{
	PlayerChoicesManager::PlayerChoicesManager(std::shared_ptr<GameObject>& owner) :
		Component(owner),
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

			if (!collision->IsUpdateActive())
			{
				continue;
			}

			auto startPosition = transform->GetWorldPosition();
			auto rayDirection = transform->GetForword();

			RayHitData hitData;
			bool isHit = collision->IsRayHit(startPosition, rayDirection, hitData);

			auto it = std::find(m_rayCollisionObjects.begin(), m_rayCollisionObjects.end(), object);

			if(isHit && hitData.length <= m_searchRange)
			{
				if (it == m_rayCollisionObjects.end())
				{
					m_rayCollisionObjects.push_back(object);

					m_playerChoicesList->AddChoice(choicesComponent->GetChoicesObjectAndEvent(GetGameObject()));
				}
			}
			else
			{
				if (it != m_rayCollisionObjects.end())
				{
					m_rayCollisionObjects.erase(it);
					m_playerChoicesList->RemoveChoice(object);
				}
			}
		}

		if (PlayerInputer::IsUpChoices())
		{
			m_playerChoicesList->AddIndex(-1);
		}

		if (PlayerInputer::IsDownChoices())
		{
			m_playerChoicesList->AddIndex(1);
		}

		if (PlayerInputer::IsDecision())
		{
			m_playerChoicesList->Invoke();
		}

	}

	void PlayerChoicesManager::AddPlayerChoice(const std::shared_ptr<ChoicesObjectAndEvent>& choicesObjectAndEvent)
	{
		m_playerChoicesList->AddChoice(choicesObjectAndEvent);
	}

	void PlayerChoicesManager::RemovePlayerChoice(const std::shared_ptr<GameObject>& choicesObject)
	{
		m_playerChoicesList->RemoveChoice(choicesObject);
	}
}