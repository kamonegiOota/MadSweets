
/*!
@file LoadData.h
@brief ���[�h�f�[�^�w�b�_�@
�S���F�ێR�T��
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
		};

		static SavingValue sm_saveValue;

		ex_weak_ptr<AlphaFadeCtrl> m_fadeCtrl;
		std::shared_ptr<GameObject> m_target;

		wstring m_nextMap = L"Stage2.csv";
		Vec3 m_position = Vec3(0.0f);

		void ChangeStageReserve();  //�X�e�[�W�ω�����
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

		//�A�N�Z�b�T---------------------------------------------------------------
		void SetNextMap(const wstring& nextMap) {
			m_nextMap = nextMap;
		}

		void SetMovePosition(const Vec3& position) {
			m_position = position;
		}


		static SavingValue GetSavingValue() {
			return sm_saveValue;
		}
	};

}

//basecross