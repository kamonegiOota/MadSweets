/*!
@file MyRandom.h
@brief MyRandom�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "EatenComponent.h"

#include "TimerDamage.h"
#include "PulledSweets.h"
#include "StomachSound.h"

namespace basecross {

	enum class WeightState;


	class HungerCompCtrl : public Component
	{
		WeightState m_beforeWeightState;  //�O��̃X�e�[�g

		ex_weak_ptr<TimerDamage> m_timerDamage;   //���Ԍo�߂Ń_���[�W���󂯂�
		ex_weak_ptr<PulledSweets> m_pulledSweets; //���َq�̕����Ɉړ����n�߂�
		ex_weak_ptr<StomachSound> m_stomachSound; //�����Ȃ鏈��

		/// <summary>
		/// ��ԕύX���ɁA�֌W����R���|�[�l���g��On,Off��؂�ւ���B
		/// </summary>
		/// <param name="isActive">�Q���Ԃ��ǂ���</param>
		void ChangeUpdateActive(const bool isActive);

		/// <summary>
		/// �Q���Ԃ��ǂ����̊Ď�
		/// </summary>
		void HungerMgr();

	public:
		HungerCompCtrl(const std::shared_ptr<GameObject>& objPtr);

		void OnCreate() override{}
		void OnStart() override;
		void OnUpdate() override;


		//�A�N�Z�b�T-----------------------------------------------------------
	};

}

//endbasecross