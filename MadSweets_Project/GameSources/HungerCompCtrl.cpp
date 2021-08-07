/*!
@file GameManager.cpp
@brief GameManager�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "HungerCompCtrl.h"


namespace basecross {

	void HungerCompCtrl::ChangeHunger(const bool isActive) {
		//�Q���ԂɂȂ����炱�̕ύX��������
		
	}

	void HungerCompCtrl::HungerMgr() {
		//�Q���Ԃ̃X�e�[�g���Ď�����B
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