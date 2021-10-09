
/*!
@file LoadData.h
@brief ロードデータヘッダ　
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "AlphaFadeCtrl.h"
#include "AlphaFadeObject.h"

#include "WeightGaugeCtrl.h"

namespace basecross {

	class LoadStageTrigger : public Component
	{
		struct SavingValue {
			float hp = 0;
			float weight = 0;
			float calorie = 0;
			WeightState weightState = WeightState::Nomal;
			bool isActive = false;

			void Reset() {
				hp = 0;
				weight = 0;
				calorie = 0;
				WeightState weightState = WeightState::Nomal;
				isActive = false;
			}
		};

		static SavingValue sm_saveValue; //セーブ用のデータ

		ex_weak_ptr<AlphaFadeCtrl> m_fadeCtrl;
		std::shared_ptr<GameObject> m_target;

		wstring m_nextMap = L"Stage2.csv";
		Vec3 m_position = Vec3(0.0f);

		/// <summary>
		/// //ステージ変化の準備
		/// </summary>
		void ChangeStageReserve();  
		/// <summary>
		/// ステージ変更時にターゲットを移動させる場所
		/// </summary>
		void MovePosition();
		void ChangeStage();
		void FadeStart();

	public:
		LoadStageTrigger(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override {}
		
		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;

		//アクセッサ---------------------------------------------------------------

		void SetNextMap(const wstring& nextMap) {
			m_nextMap = nextMap;
		}

		void SetMovePosition(const Vec3& position) {
			m_position = position;
		}

		//セーブ用のデータ
		static SavingValue GetSavingValue() {
			auto saveValue = sm_saveValue;
			sm_saveValue.isActive = false;
			return saveValue;
		}
	};

}

//basecross