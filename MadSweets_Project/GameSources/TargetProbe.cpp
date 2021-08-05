/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "TargetProbe.h"
#include "AstarCtrl.h"
#include "SearchHidden.h"
#include "BaseEnemy.h"
#include "EnState_LoseTarget.h"

namespace basecross {

	void TargetProbe::SetAstarRondomHideObject() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			//近くのオブジェクトからランダムに捜索対象のオブジェクトを選択。
			auto hideObj = SearchHidden::SearchRandomHiddenObject(GetGameObject(), m_searchRange, m_checkHideObj);

			if (hideObj == nullptr) {  //近くに隠れるオブジェクトが無かったら
				ChangeState();
				return;
			}

			astar->SearchAstarStart(hideObj);
			m_checkHideObj = hideObj;
		}
	}

	void TargetProbe::ChangeState() {
		m_probCount = 0;

		auto enemy = GetGameObject()->GetComponent<BaseEnemy>();
		if (enemy) {
			enemy->ChangeStateMachine<EnState_LoseTarget>();  //見失った状態にする。
		}
	}

	void TargetProbe::RouteEnd() {
		//本来はここでオブジェクトの中を覗く処理。
		m_probCount++;

		if (m_probCount >= m_numPorb) {  //指定回数調べたら。
			ChangeState();
		}
		else {  //まだカウントが過ぎていなかったら。
			SetAstarRondomHideObject();  //もう一度調べる。
		}
	}

	void TargetProbe::Move() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>();
		if (astar) {
			astar->UpdateVelocityMove(GetVelocityMaxSpeed(), GetArriveNearRange());

			if (astar->IsRouteEnd()) {
				RouteEnd();
			}
		}
	}

	void TargetProbe::OnCreate() {
		SetUpdateActive(false);
	}

	void TargetProbe::OnUpdate() {
		Move();
	}

	void TargetProbe::StartProb() {
		m_probCount = 0;
		m_checkHideObj = nullptr;
		SetAstarRondomHideObject();
	}

}

//endbasecross