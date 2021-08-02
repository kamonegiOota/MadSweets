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

		std::shared_ptr<ChoicesObjectAndEvent> m_choiceObjectAndEventPtr;
	public:
		EatenComponent(std::shared_ptr<GameObject>& owner,const EatenData& eatenData);

		EatenData GetEatenData() const;

		std::shared_ptr<ChoicesObjectAndEvent const> GetChoicesObjectAndEvent(const std::shared_ptr<GameObject>& selectorObject) override;
	};
}