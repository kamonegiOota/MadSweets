/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "TargetProbe.h"
#include "AstarCtrl.h"
#include "SearchHidden.h"

namespace basecross {

	void TargetProbe::SetAstarRondomHideObject() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>();
		if (astar) {
			//近くのオブジェクトからランダムに捜索対象のオブジェクトを選択。
			auto hideObj = SearchHidden::SearchRandomHiddenObject(GetGameObject());

			astar->SearchAstarStart(hideObj);
		}
	}

	void TargetProbe::ChangeState() {

	}

	void TargetProbe::RouteEnd() {
		m_probCount++;

		if (m_probCount >= m_numPorb) {
			m_probCount = 0;
			ChangeState();
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
		SetAstarRondomHideObject();
	}

}

//endbasecross