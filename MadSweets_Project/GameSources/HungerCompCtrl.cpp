/*!
@file HungerCompCtrl.cpp
@brief HungerCompCtrl�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "HungerCompCtrl.h"
#include "PlayerWeightManager.h"

#include "DebugObject.h"

namespace basecross {

	HungerCompCtrl::HungerCompCtrl(const std::shared_ptr<GameObject>& objPtr)
		:Component(objPtr),m_beforeWeightState(WeightState::Nomal)
	{}

	void HungerCompCtrl::ChangeUpdateActive(const bool isActive) {
		//�Q���ԂɂȂ����炱�̕ύX��������
		ex_weak_ptr<Component> comps[] = {
			{m_timerDamage.GetShard()},
			{m_pulledSweets.GetShard()},
			{m_stomachSound.GetShard()},
		};

		for (auto& comp : comps) {
			if (comp) {
				if (comp->GetUpdateActive() != isActive) {  //������ԂȂ珈�������Ȃ��B
					comp->SetUpdateActive(isActive);
				}
			}
		}
	}

	void HungerCompCtrl::HungerMgr() {
		//�Q���Ԃ̃X�e�[�g���Ď�����B
		auto weightMgr = GetGameObject()->GetComponent<PlayerWeightManager>(false);
		if (weightMgr) {
			auto state = weightMgr->GetState();
			//�O��̃X�e�[�g�ƈꏏ�Ȃ�Ώ��������Ȃ�
			if (m_beforeWeightState == state) {  
				return;
			}

			if (state == WeightState::Hunger) {
				ChangeUpdateActive(true);
			}
			else {
				ChangeUpdateActive(false);
			}

			m_beforeWeightState = state;
		}
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