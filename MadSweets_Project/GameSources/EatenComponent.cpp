#include"EatenComponent.h"
#include"PlayerWeightManager.h"
#include "PlayerWeightMgr.h"

namespace basecross
{
	EatenData::EatenData() :
		weightValue(0.0f),
		calorieValue(0.0f)
	{}

	EatenData::EatenData(const float weightValue, const float calorieValue) :
		weightValue(weightValue),
		calorieValue(calorieValue)
	{}

	EatenComponent::EatenComponent(std::shared_ptr<GameObject>& owner,const EatenData& eatenData) :
		ChoicesComponentBase(owner),
		m_eatenData(eatenData)
	{}

	EatenData EatenComponent::GetEatenData() const
	{
		return m_eatenData;
	}

	std::shared_ptr<ChoicesObjectAndEvent const> EatenComponent::GetChoicesObjectAndEvent(const std::shared_ptr<GameObject>& selectorObject)
	{
		//本来↑はweightではなくカロリー
		auto weightManager = selectorObject->GetComponent<PlayerWeightManager>(false);
		auto weightMgr = selectorObject->GetComponent<PlayerWeightMgr>(false);

		std::function<void()> eventFunction = []() {};

		float weight = m_eatenData.weightValue;

		if (weightManager && weightMgr)
		{
			eventFunction = [this,weightManager,weightMgr]()
			{
				weightManager->AddWeight(m_eatenData.calorieValue);
				weightMgr->AddWeight(m_eatenData.weightValue);

				GetGameObject()->Destroy();
			};
		}

		if (m_choiceObjectAndEventPtr)
		{
			m_choiceObjectAndEventPtr->eventFunction = eventFunction;
			return m_choiceObjectAndEventPtr;
		}


		m_choiceObjectAndEventPtr = std::make_shared<ChoicesObjectAndEvent>(ChoicesObjectAndEvent(L"食べる", GetGameObject(), eventFunction));

		return m_choiceObjectAndEventPtr;
	}
}