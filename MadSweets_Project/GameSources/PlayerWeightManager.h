/*!
@file PlayerWeightManager.h
@brief PlayerWeightManagerクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "WeightGaugeCtrl.h"

namespace basecross {

	class WeightGaugeCtrl;

	class PlayerWeightManager : public Component
	{
		ex_weak_ptr<WeightGaugeCtrl> m_gaugeCtrl;

	public:
		PlayerWeightManager(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnStart() override;
		void OnUpdate() override;


		//アクセッサ--------------------------------------------------

		void AddWeight(const float& value);

		WeightState GetState() const;

		void SetWeightGaugeCtrl(const std::shared_ptr<WeightGaugeCtrl>& gaugeCtrl) {
			m_gaugeCtrl = gaugeCtrl;
		}

		void SetWeight(const float& value);
		float GetWeight() const {
			return m_gaugeCtrl->GetNowGauge();
		}
	};

}

//endbasecross