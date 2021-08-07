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

	class HungerCompCtrl : public Component
	{
		ex_weak_ptr<TimerDamage> m_timerDamage;
		ex_weak_ptr<PulledSweets> m_pulledSweets;
		ex_weak_ptr<StomachSound> m_stomachSound;

		//�Q���ԂɕύX
		void ChangeHunger(const bool isActive);

		//�Q���Ԃ̊Ď�
		void HungerMgr();

	public:
		HungerCompCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnStart() override;
		void OnUpdate() override;


		//�A�N�Z�b�T-----------------------------------------------------------
	};

}

//endbasecross