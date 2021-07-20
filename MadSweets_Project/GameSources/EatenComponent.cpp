#include"EatenComponent.h"
#include"PlayerWeightManager.h"

namespace basecross
{
	EatenData::EatenData() :
		weightValue(0.0f),
		calorieValue(0.0f)
	{
	}

	EatenData::EatenData(const float weightValue, const float calorieValue) :
		weightValue(weightValue),
		calorieValue(calorieValue)
	{
		
	}

	EatenComponent::EatenComponent(std::shared_ptr<GameObject>& owner,const EatenData& eatenData) :
		ChoicesComponentBase(owner),
		m_eatenData(eatenData)
	{

	}

	EatenData EatenComponent::GetEatenData() const
	{
		return m_eatenData;
	}

	ChoicesObjectAndEvent EatenComponent::GetChoicesObjectAndEvent(std::shared_ptr<GameObject>& selectorObject) const
	{
		auto weightManager = selectorObject->GetComponent<PlayerWeightManager>(false);

		std::function<void()> eventFunction = []() {};

		float weight = m_eatenData.weightValue;

		if (weightManager)
		{
			eventFunction = [this,weightManager]()
			{
				weightManager->AddWeight(m_eatenData.weightValue);

				GetGameObject()->Destroy();
			};
		}

		return ChoicesObjectAndEvent(L"êHÇ◊ÇÈ", GetGameObject(), eventFunction);
	}
}