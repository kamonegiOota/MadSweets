/*!
@file PositionDrawComp.h
@brief PositionDrawComp
担当者：丸山 裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "PlayerWeightMgr.h"

#include "MyUtility.h"

#include "DebugObject.h"

namespace basecross {

	void PlayerWeightMgr::OnCreate() {
		//if (!m_gaugeCtrl) { //ゲージが存在しなかったら
		//	m_gaugeCtrl = maru::MyUtility::GetComponent<WeightGaugeCtrl>();
		//}
	}

	void PlayerWeightMgr::OnStart() {
		
	}

	void PlayerWeightMgr::OnUpdate() {
		//test的に無かったらここで取得するようにしておく
		if (!m_gaugeCtrl) {
			m_gaugeCtrl = maru::MyUtility::GetComponent<WeightGaugeCtrl>();
		}
	}

	//アクセッサ--------------------------------------------------
	void PlayerWeightMgr::AddWeight(const float& value) {
		//生成の順番を間違えた時用
		//存在しなかったら一度検索
		if (!m_gaugeCtrl) {
			m_gaugeCtrl = maru::MyUtility::GetComponent<WeightGaugeCtrl>();
		}

		if (m_gaugeCtrl) {
			m_gaugeCtrl->AddGauge(value);
		}
	}

	WeightState PlayerWeightMgr::GetState() const {
		if (m_gaugeCtrl) {
			return m_gaugeCtrl->GetState();
		}
		else {
			return WeightState::None;
			DebugObject::sm_wss << endl << L"PlayerWeightMgr::GetState() , m_gaugeCtrlが存在しません。";
		}
	}

	void PlayerWeightMgr::SetWeight(const float& value) {
		if (!m_gaugeCtrl) {
			m_gaugeCtrl = maru::MyUtility::GetComponent<WeightGaugeCtrl>();
		}

		m_gaugeCtrl->SetNowGauge(value);
	}

}

//endbasecross