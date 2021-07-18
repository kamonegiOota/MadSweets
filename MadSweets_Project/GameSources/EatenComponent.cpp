#include"EatenComponent.h"

namespace basecross
{
	EatenData::EatenData() :
		weightValue(0.0f)
	{
	}

	EatenData::EatenData(const float weightValue) :
		weightValue(weightValue)
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