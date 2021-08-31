/*!
@file PositionDrawComp.h
@brief PositionDrawComp
�S���ҁF�ێR �T��
*/

#include "stdafx.h"
#include "Project.h"
#include "PlayerWeightMgr.h"

#include "MyUtility.h"

#include "DebugObject.h"

namespace basecross {

	void PlayerWeightMgr::OnCreate() {
		//if (!m_gaugeCtrl) { //�Q�[�W�����݂��Ȃ�������
		//	m_gaugeCtrl = maru::MyUtility::GetComponent<WeightGaugeCtrl>();
		//}
	}

	void PlayerWeightMgr::OnStart() {
		
	}

	void PlayerWeightMgr::OnUpdate() {
		//test�I�ɖ��������炱���Ŏ擾����悤�ɂ��Ă���
		if (!m_gaugeCtrl) {
			m_gaugeCtrl = maru::MyUtility::GetComponent<WeightGaugeCtrl>();
		}
	}

	//�A�N�Z�b�T--------------------------------------------------
	void PlayerWeightMgr::AddWeight(const float& value) {
		//�����̏��Ԃ��ԈႦ�����p
		//���݂��Ȃ��������x����
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
			DebugObject::sm_wss << endl << L"PlayerWeightMgr::GetState() , m_gaugeCtrl�����݂��܂���B";
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