#include"EatenComponent.h"
#include"PlayerCalorieManager.h"
#include "PlayerWeightManager.h"
#include "PlayerStatusManager.h"

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

	map<wstring, EatenData> EatenComponent::sm_defaultDatas = {
		{L"SweetHand_Tx", EatenData(50.0f, 50.0f)},
		{L"SweetCokie_Tx", EatenData(30.0f, 70.0f)},
		{L"SweetEye_Tx", EatenData(100.0f, 30.0f)},
	};

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
		auto calorieManager = selectorObject->GetComponent<PlayerCalorieManager>(false);
		auto weightMgr = selectorObject->GetComponent<PlayerWeightManager>(false);
		auto player = selectorObject->GetComponent<PlayerStatusManager>(false);

		std::function<void()> eventFunction = []() {};

		float weight = m_eatenData.weightValue;

		if (calorieManager && weightMgr && player)
		{
			eventFunction = [this, calorieManager,weightMgr, player]()
			{
				calorieManager->AddCalorie(m_eatenData.calorieValue);
				weightMgr->AddWeight(m_eatenData.weightValue);
				player->AddHP(1.0f);

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