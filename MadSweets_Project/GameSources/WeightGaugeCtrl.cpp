/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

#include "WeightGaugeCtrl.h"
#include "ScalePop.h"

namespace basecross {

	WeightGaugeCtrl::WeightGaugeCtrl(const std::shared_ptr<GameObject>& objPtr,
		const std::shared_ptr<UIObject>& frame,
		const std::shared_ptr<UIObject>& gauge
	) :
		WeightGaugeCtrl(objPtr, frame, gauge, map<WeightState, WeightGaugeParam>())
	{}

	WeightGaugeCtrl::WeightGaugeCtrl(const std::shared_ptr<GameObject>& objPtr,
		const std::shared_ptr<UIObject>& frame,
		const std::shared_ptr<UIObject>& gauge,
		const map<WeightState, WeightGaugeParam>& params
	) :
		Component(objPtr),
		m_frameUI(frame),
		m_gaugeUI(gauge),
		m_params(params)
	{}

	void WeightGaugeCtrl::CreateParametor() {
		if (!m_params.empty()) {  //empty�łȂ������珉�����͂��Ȃ��B
			return;
		}
		//normal
		m_params[WeightState::Nomal] = WeightGaugeParam(100.0f,L"NomalFont_Tx",L"NomalGauge_Tx",
			WeightState::Chubby, WeightState::Hunger);
		//�����Ă���
		m_params[WeightState::Chubby] = WeightGaugeParam(100.0f, L"ChubbyFont_Tx", L"ChubbyGauge_Tx",
			WeightState::None, WeightState::Nomal);
		//�����Ă���
		//m_params[WeightState::Skinny] = WeightGaugeParam(100.0f, L"SkinnyFont_Tx", L"SkinnyGauge_Tx",
		//	WeightState::Nomal, WeightState::Hunger);
		//�Q��
		m_params[WeightState::Hunger] = WeightGaugeParam(100.0f, L"HungerFont_Tx", L"HungerGauge_Tx",
			WeightState::Nomal, WeightState::None);
	}

	void WeightGaugeCtrl::GaugeCheck() {
		//�ő�l���傫��������
		if (m_gaugeValue > m_params[m_state].maxGauge) {
			GaugeMaxProcess();
		}
		
		//0��菬����������
		if (m_gaugeValue <= 0.0f) {
			GaugeMinProcess();
		}
	}

	void WeightGaugeCtrl::GaugeMaxProcess() {
		//��̃X�e�[�g�����݂��Ȃ��ꍇ
		if (m_params[m_state].upChangeState == WeightState::None) {
			m_gaugeValue = m_params[m_state].maxGauge;
			return;
		}

		auto more = m_gaugeValue - m_params[m_state].maxGauge; //�˂��o���������v�Z
		m_gaugeValue = more;

		ChangeState(m_params[m_state].upChangeState);
		ChangeTexture();
		PopScale();
	}

	void WeightGaugeCtrl::GaugeMinProcess() {
		//���̃X�e�[�g�����݂��Ȃ��ꍇ
		if (m_params[m_state].downChangeState == WeightState::None) {
			m_gaugeValue = 0.0f;
			return;
		}

		ChangeState(m_params[m_state].downChangeState);

		auto more = m_params[m_state].maxGauge - m_gaugeValue; //�˂��o���������v�Z
		m_gaugeValue = more;
		ChangeTexture();
	}

	void WeightGaugeCtrl::GaugeUpdate() {
		//���ŏオ�艺���肷��悤�ɂ����B
		auto& key = App::GetApp()->GetMyInputDevice()->GetKeyBoard();

		if (key.IsInputDown(itbs::Input::KeyCode::UpArrow)) {
			AddGauge(10.0f);
		}

		if (key.IsInputDown(itbs::Input::KeyCode::DownArrow)) {
			AddGauge(-10.0f);
		}

		auto fill = m_gaugeValue / m_params[m_state].maxGauge;
		m_gaugeUI->GetComponent<Image>()->SetFillAmount(fill);
	}

	void WeightGaugeCtrl::ChangeTexture() {
		auto param = m_params[m_state];
		m_frameUI->GetComponent<Image>()->SetTextureResource(param.frameTx);
		m_gaugeUI->GetComponent<Image>()->SetTextureResource(param.gaugeTx);
	}

	void WeightGaugeCtrl::PopScale() {
		float speed = 3.0f;
		float startSize = 0.5f;
		m_frameUI->GetComponent<ScalePop>()->StartPop(speed, startSize);
		m_gaugeUI->GetComponent<ScalePop>()->StartPop(speed, startSize);
	}

	void WeightGaugeCtrl::TimeMgr() {
		auto delta = App::GetApp()->GetElapsedTime();
		m_timeElapsed += delta;

		if (m_timeElapsed > m_time) {
			m_timeElapsed = 0.0f;
			AddGauge(m_timeDownValue);
		}
	}

	void WeightGaugeCtrl::OnCreate() {
		CreateParametor();
		m_frameUI->AddComponent<ScalePop>();
		m_gaugeUI->AddComponent<ScalePop>();
	}

	void WeightGaugeCtrl::OnUpdate() {
		GaugeUpdate();

		TimeMgr();
	}

}

//endbasecross