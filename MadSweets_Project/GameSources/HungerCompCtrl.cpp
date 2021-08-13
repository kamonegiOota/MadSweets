/*!
@file GameManager.cpp
@brief GameManagerクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "HungerCompCtrl.h"
#include "PlayerWeightMgr.h"

#include "DebugObject.h"

namespace basecross {

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

		//m_pulledSweets->SetUpdateActive(isActive);
	}

	void HungerCompCtrl::HungerMgr() {
		//飢餓状態のステートを監視する。
		//testが終了したらステートが切り替わったタイミングでのみ呼ばれるように調整する。
		auto weightMgr = GetGameObject()->GetComponent<PlayerWeightMgr>(false);
		if (weightMgr) {
			auto state = weightMgr->GetState();
			if (state == WeightState::Hunger) {
				ChangeUpdateActive(true);
			}
			else {
				ChangeUpdateActive(false);
			}
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