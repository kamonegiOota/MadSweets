#include"PlayerEatManager.h"
#include"EatenComponent.h"

namespace basecross
{
	PlayerEatManager::PlayerEatManager(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void PlayerEatManager::OnCreate()
	{
		m_weightManager = GetGameObject()->GetComponent<PlayerWeightManager>();
	}

	void PlayerEatManager::OnCollisionEnter(std::shared_ptr<GameObject>& other)
	{
		auto eatenComponent = other->GetComponent<EatenComponent>(false);

		if (!eatenComponent)
		{
			return;
		}

		m_weightManager->AddWeight(eatenComponent->GetEatenData().weightValue);

		other->Destroy();
	}
}