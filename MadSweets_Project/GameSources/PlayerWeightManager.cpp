/*!
@file PlayerWeightManager.h
@brief PlayerWeightManager
�S���ҁF�ێR �T��
*/

#include "stdafx.h"
#include "Project.h"
#include "PlayerWeightManager.h"

#include "MyUtility.h"

#include "DebugObject.h"

namespace basecross {

	void PlayerWeightManager::OnCreate() {
		if (!m_gaugeCtrl) { //�Q�[�W�����݂��Ȃ�������
			m_gaugeCtrl = maru::MyUtility::GetComponent<WeightGaugeCtrl>(GetStage());
		}
	}

	void PlayerWeightManager::OnStart() {
		
	}

	void PlayerWeightManager::OnUpdate() {
		//test�I�ɖ��������炱���Ŏ擾����悤�ɂ��Ă���
		if (!m_gaugeCtrl) {
			m_gaugeCtrl = maru::MyUtility::GetComponent<WeightGaugeCtrl>();
		}
	}

	//�A�N�Z�b�T--------------------------------------------------

	void PlayerWeightManager::AddWeight(const float& value) {
		//�����̏��Ԃ��ԈႦ�����p
		//���݂��Ȃ��������x����
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
			DebugObject::sm_wss << endl << L"PlayerWeightManager::GetState() , m_gaugeCtrl�����݂��܂���B";
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