#pragma once
#include"ChoicesComponentBase.h"

namespace basecross
{
	struct EatenData
	{
		float weightValue;

		float calorieValue;

		EatenData();

		EatenData(const float weightValue,const float calorieValue);
	};

	class EatenComponent : public ChoicesComponentBase
	{
		EatenData m_eatenData;
	public:
		EatenComponent(std::shared_ptr<GameObject>& owner,const EatenData& eatenData);

		EatenData GetEatenData() const;

		ChoicesObjectAndEvent GetChoicesObjectAndEvent(std::shared_ptr<GameObject>& selectorObject) const override;

		void OnUpdate() override {}
	};
}