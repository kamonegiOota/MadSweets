/*!
@file HungerCompCtrl.cpp
@brief HungerCompCtrlクラス実体
担当：丸山裕喜
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
		//飢餓状態になったらこの変更を加える
		ex_weak_ptr<Component> comps[] = {
			{m_timerDamage.GetShard()},
			{m_pulledSweets.GetShard()},
			{m_stomachSound.GetShard()},
		};

		for (auto& comp : comps) {
			if (comp) {
				if (comp->GetUpdateActive() != isActive) {  //同じ状態なら処理をしない。
					comp->SetUpdateActive(isActive);
				}
			}
		}
	}

	void HungerCompCtrl::HungerMgr() {
		//飢餓状態のステートを監視する。
		auto weightMgr = GetGameObject()->GetComponent<PlayerWeightManager>(false);
		if (weightMgr) {
			auto state = weightMgr->GetState();
			//前回のステートと一緒ならば処理をしない
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