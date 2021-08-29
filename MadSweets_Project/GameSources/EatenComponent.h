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

		//ŠÛŽR’Ç‹L•ª
		void operator=(const EatenData& data) {
			weightValue = data.weightValue;
			calorieValue = data.calorieValue;
		}

		void operator+=(const EatenData& data) {
			weightValue += data.weightValue;
			calorieValue += data.calorieValue;
		}

		void operator-=(const EatenData& data) {
			weightValue -= data.weightValue;
			calorieValue -= data.calorieValue;
		}
	};

	class EatenComponent : public ChoicesComponentBase
	{
		EatenData m_eatenData;

		std::shared_ptr<ChoicesObjectAndEvent> m_choiceObjectAndEventPtr;
	public:
		EatenComponent(std::shared_ptr<GameObject>& owner,const EatenData& eatenData);

		void SetEatenData(const EatenData& data) {
			m_eatenData = data;
		}

		EatenData GetEatenData() const;

		std::shared_ptr<ChoicesObjectAndEvent const> GetChoicesObjectAndEvent(const std::shared_ptr<GameObject>& selectorObject) override;
	};
}