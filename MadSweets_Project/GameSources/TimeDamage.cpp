
/*!
@file GameManager.cpp
@brief GameManagerƒNƒ‰ƒXŽÀ‘Ì
’S“–FŠÛŽR—TŠì
*/

#include "stdafx.h"
#include "Project.h"

#include "TimerDamage.h"
#include "I_Damaged.h"

namespace basecross {

	void TimerDamage::Damage() {
		auto damage = GetGameObject()->GetComponent<I_Damaged>();
		if (damage) {
			damage->Damage(m_power);
		}
	}

	void TimerDamage::TimeMgr() {
		auto delta = App::GetApp()->GetElapsedTime();
		m_timeElapsed += delta;

		if (m_timeElapsed > m_time) {
			m_timeElapsed = 0.0f;
			Damage();
		}
	}

	void TimerDamage::OnCreate() {
		//SetUpdateActive(false);
	}

	void TimerDamage::OnUpdate() {
		TimeMgr();
	}

}

//endbasecross