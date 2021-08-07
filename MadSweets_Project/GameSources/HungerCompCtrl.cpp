/*!
@file GameManager.cpp
@brief GameManagerクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "HungerCompCtrl.h"


namespace basecross {

	void HungerCompCtrl::ChangeHunger(const bool isActive) {
		//飢餓状態になったらこの変更を加える
		
	}

	void HungerCompCtrl::HungerMgr() {
		//飢餓状態のステートを監視する。
	}

	void HungerCompCtrl::OnStart() {
		auto obj = GetGameObject();
		m_timerDamage = obj->GetComponent<TimerDamage>();
		m_pulledSweets = obj->GetComponent<PulledSweets>();
		m_stomachSound = obj->GetComponent<StomachSound>();
	}

	void HungerCompCtrl::OnUpdate() {
		HungerMgr();
	}

}

//endbasecross