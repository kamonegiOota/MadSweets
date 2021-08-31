#include"PlayerEatManager.h"
#include"EatenComponent.h"

namespace basecross
{
	PlayerEatManager::PlayerEatManager(std::shared_ptr<GameObject>& owner, std::shared_ptr<GameObject> playerCamera) :
		Component(owner),
		m_playerCameraObject(playerCamera)
	{

	}

	void PlayerEatManager::OnCreate()
	{
		m_calorieManager = GetGameObject()->GetComponent<PlayerCalorieManager>();
	}

	void PlayerEatManager::OnUpdate()
	{
		auto startPosition = transform->GetWorldPosition();
		auto searchEndPosition = startPosition + m_playerCameraObject->GetComponent<Transform>()->GetForword() * m_searchRange;

		for (auto& object : GetStage()->GetGameObjectVec())
		{
			auto eatenComponent = object->GetComponent<EatenComponent>(false);

			if (!eatenComponent)
			{
				continue;
			}

			auto collision = object->GetComponent<Collision>(false);

			if (!collision)
			{
				continue;
			}

			if (collision->IsRayHit(startPosition, searchEndPosition))
			{
				m_calorieManager->AddCalorie(eatenComponent->GetEatenData().weightValue);

				object->Destroy();
			}
		}
	}

	void PlayerEatManager::OnCollisionEnter(std::shared_ptr<GameObject>& other)
	{
		//auto eatenComponent = other->GetComponent<EatenComponent>(false);

		//if (!eatenComponent)
		//{
		//	return;
		//}

		//m_weightManager->AddWeight(eatenComponent->GetEatenData().weightValue);

		//other->Destroy();
	}
}