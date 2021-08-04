/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
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
			//�߂��̃I�u�W�F�N�g���烉���_���ɑ{���Ώۂ̃I�u�W�F�N�g��I���B
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