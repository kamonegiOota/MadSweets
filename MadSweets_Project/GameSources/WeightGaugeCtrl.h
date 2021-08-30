/*!
@file MaruStage.h
@brief MaruStage
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//class PlayerWeightMgr;

	enum class WeightState {
		Nomal,
		Chubby, //�f�u
		Skinny, //����
		Hunger, //�Q��
		None, //null�̂悤�Ɉ����悤�A���݂��Ȃ��Ƃ��p
	};

	struct WeightGaugeParam
	{
		float maxGauge = 100.0f;
		wstring frameTx = L"";  //�t���[���̃e�N�X�`��
		wstring gaugeTx = L"";  //�Q�[�W�̃e�N�X�`��

		WeightState upChangeState;   //�Q�[�W��max���ɂǂ̃X�e�[�g�ɐ؂�ւ��邩
		WeightState downChangeState; //�Q�[�W��min���ɂǂ̃X�e�[�g�ɐ؂�ւ��邩

		WeightGaugeParam()
			:WeightGaugeParam(100.0f,L"",L"", WeightState::None, WeightState::None)
		{}

		WeightGaugeParam(const float& maxGauge, const wstring& frameTx, const wstring& gaugeTx,
			const WeightState& upChangeState, const WeightState& downChangeState
		):
			maxGauge(maxGauge),frameTx(frameTx), gaugeTx(gaugeTx),
			upChangeState(upChangeState), downChangeState(downChangeState)
		{}
	};


	class WeightGaugeCtrl : public Component
	{
		//ex_weak_ptr<PlayerWeightMgr> m_weightMgr;

		std::shared_ptr<UIObject> m_frameUI;
		std::shared_ptr<UIObject> m_gaugeUI;

		float m_gaugeValue = 50.0f;
		WeightState m_state = WeightState::Nomal;

		map<WeightState, WeightGaugeParam> m_params;

		//��莞�ԂŌ��鏈��
		float m_timeElapsed = 0.0f;
		float m_time = 20.0f;
		float m_timeDownValue = -1.0f;  //��莞�ԂŌ����

		//�p�����[�^�̐���
		void CreateParametor();

		//�Q�[�W�̏�ԃ`�F�b�N
		void GaugeCheck();
		//�Q�[�W���ő�ɂȂ����Ƃ��ɂ��鏈��
		virtual void GaugeMaxProcess();
		//�Q�[�W��0������������ɂ��鏈��
		virtual void GaugeMinProcess();

		void GaugeUpdate();  //�Q�[�W�̃R���g���[��
		void ChangeTexture(); //�e�N�X�`���̕ύX
		void PopScale();  //PopScale�����邽�߂̏���

		void TimeMgr();

	public:

		WeightGaugeCtrl(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<UIObject>& frame,
			const std::shared_ptr<UIObject>& gauge
		);

		WeightGaugeCtrl(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<UIObject>& frame,
			const std::shared_ptr<UIObject>& gauge,
			const map<WeightState, WeightGaugeParam>& params
		);

		void OnCreate() override;
		void OnUpdate() override;

		//�A�N�Z�b�T----------------------------------------------------------------------

		//�Q�[�W�̒ǉ��A�팸
		virtual void AddGauge(const float& value) final {
			m_gaugeValue += value;
			GaugeCheck();
		}

		virtual void SetNowGauge(const float& value) final {
			m_gaugeValue = value;
		}
		virtual float GetNowGauge() const final {
			return m_gaugeValue;
		}

		void ChangeState(const WeightState& state) {
			m_state = state;
		}
		WeightState GetState() const {
			return m_state;
		}

		void SetTime(const float& time) {
			m_time = time;
		}

		void SetTimeDownValue(const float& value) {
			m_timeDownValue = value;
		}
	};

}

//endbasecross