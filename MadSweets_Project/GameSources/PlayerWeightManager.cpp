/*!
@file PlayerWeightManager.h
@brief PlayerWeightManager
担当者：丸山 裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "PlayerWeightManager.h"

#include "MyUtility.h"

#include "DebugObject.h"

namespace basecross {

	void PlayerWeightManager::OnCreate() {
		if (!m_gaugeCtrl) { //ゲージが存在しなかったら
			m_gaugeCtrl = maru::MyUtility::GetComponent<WeightGaugeCtrl>(GetStage());
		}
	}

	void PlayerWeightManager::OnStart() {
		
	}

	void PlayerWeightManager::OnUpdate() {
		//test的に無かったらここで取得するようにしておく
		if (!m_gaugeCtrl) {
			m_gaugeCtrl = maru::MyUtility::GetComponent<WeightGaugeCtrl>();
		}
	}

	//アクセッサ--------------------------------------------------

	void PlayerWeightManager::AddWeight(const float& value) {
		//生成の順番を間違えた時用
		//存在しなかったら一度検索
		if (!m_gaugeCtrl) {
			m_gaugeCtrl = maru::MyUtility::GetComponent<WeightGaugeCtrl>();
		}

		if (m_gaugeCtrl) {
			m_gaugeCtrl->AddGauge(value);
		}
	}

	WeightState PlayerWeightManager::GetState() const {
		if (m_gaugeCtrl) {
			return m_gaugeCtrl->GetState();
		}
		else {
			return WeightState::None;
			DebugObject::sm_wss << endl << L"PlayerWeightManager::GetState() , m_gaugeCtrlが存在しません。";
		}
	}

	void PlayerWeightManager::SetWeight(const float& value) {
		if (!m_gaugeCtrl) {
			m_gaugeCtrl = maru::MyUtility::GetComponent<WeightGaugeCtrl>();
		}

		m_gaugeCtrl->SetNowGauge(value);
	}

}

//endbasecross