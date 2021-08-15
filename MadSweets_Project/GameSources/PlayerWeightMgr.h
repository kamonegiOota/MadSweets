/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "WeightGaugeCtrl.h"

namespace basecross {

	class WeightGaugeCtrl;

	class PlayerWeightMgr : public Component
	{
		ex_weak_ptr<WeightGaugeCtrl> m_gaugeCtrl;

		//WeightState m_state = WeightState::Nomal;
		
	public:
		PlayerWeightMgr(const std::shared_ptr<GameObject>& objPtr)
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
	};

}

//endbasecross