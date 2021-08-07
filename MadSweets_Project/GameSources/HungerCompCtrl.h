/*!
@file MyRandom.h
@brief MyRandomクラス
担当：丸山裕喜
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

		//飢餓状態に変更
		void ChangeHunger(const bool isActive);

		//飢餓状態の監視
		void HungerMgr();

	public:
		HungerCompCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnStart() override;
		void OnUpdate() override;


		//アクセッサ-----------------------------------------------------------
	};

}

//endbasecross