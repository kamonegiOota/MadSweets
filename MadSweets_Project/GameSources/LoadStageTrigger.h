
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
			bool isActive = false;

			void Reset() {
				hp = 0;
				weight = 0;
				calorie = 0;
				WeightState weightState = WeightState::Nomal;
				isActive = false;
			}
		};

		static SavingValue sm_saveValue; //�Z�[�u�p�̃f�[�^

		ex_weak_ptr<AlphaFadeCtrl> m_fadeCtrl;
		std::shared_ptr<GameObject> m_target;

		wstring m_nextMap = L"Stage2.csv";
		Vec3 m_position = Vec3(0.0f);

		/// <summary>
		/// //�X�e�[�W�ω��̏���
		/// </summary>
		void ChangeStageReserve();  
		/// <summary>
		/// �X�e�[�W�ύX���Ƀ^�[�Q�b�g���ړ�������ꏊ
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

		//�A�N�Z�b�T---------------------------------------------------------------

		void SetNextMap(const wstring& nextMap) {
			m_nextMap = nextMap;
		}

		void SetMovePosition(const Vec3& position) {
			m_position = position;
		}

		//�Z�[�u�p�̃f�[�^
		static SavingValue GetSavingValue() {
			auto saveValue = sm_saveValue;
			sm_saveValue.isActive = false;
			return saveValue;
		}
	};

}

//basecross