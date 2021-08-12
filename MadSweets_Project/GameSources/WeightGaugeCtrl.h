/*!
@file MaruStage.h
@brief MaruStage
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "StateMachine.h"

namespace basecross {

	enum class WeightState {
		Nomal,
		Chubby, //デブ
		Skinny, //痩せ
		Hunger, //飢餓
		None, //nullのように扱うよう、存在しないとき用
	};

	struct WeightGaugeParam
	{
		float maxGauge = 100.0f;
		wstring frameTx = L"";  //フレームのテクスチャ
		wstring gaugeTx = L"";  //ゲージのテクスチャ

		WeightState upChangeState = WeightState::None;   //ゲージがmax時にどのステートに切り替えるか
		WeightState downChangeState = WeightState::None; //ゲージがmin時にどのステートに切り替えるか

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
		std::shared_ptr<UIObject> m_frameUI;
		std::shared_ptr<UIObject> m_gaugeUI;

		float m_gaugeValue = 50.0f;
		WeightState m_state = WeightState::Nomal;

		map<WeightState, WeightGaugeParam> m_params;

		//パラメータの生成
		void CreateParametor();

		//ゲージの状態チェック
		void GaugeCheck();
		//ゲージが最大になったときにする処理
		virtual void GaugeMaxProcess();
		//ゲージが0を下回った時にする処理
		virtual void GaugeMinProcess();

		void GaugeUpdate();  //ゲージのコントロール
		void ChangeTexture(); //テクスチャの変更

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

		//アクセッサ----------------------------------------------------------------------

		//ゲージの追加、削減
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
	};

}

//endbasecross