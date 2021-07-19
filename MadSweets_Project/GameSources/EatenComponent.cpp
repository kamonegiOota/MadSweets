#include"EatenComponent.h"

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
		Component(owner),
		m_eatenData(eatenData)
	{

	}

	EatenData EatenComponent::GetEatenData() const
	{
		return m_eatenData;
	}
}