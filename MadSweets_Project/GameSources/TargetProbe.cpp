/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
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
			//�߂��̃I�u�W�F�N�g���烉���_���ɑ{���Ώۂ̃I�u�W�F�N�g��I���B
			auto hideObj = SearchHidden::SearchRandomHiddenObject(GetGameObject(), m_searchRange, m_checkHideObj);

			if (hideObj == nullptr) {  //�߂��ɉB���I�u�W�F�N�g������������
				ChangeState();
				return;
			}

			astar->SearchAstarStart(hideObj);
			m_checkHideObj = hideObj;
		}
	}

	void TargetProbe::ChangeState() {

		auto enemy = GetGameObject()->GetComponent<BaseEnemy>();
		if (enemy) {
			enemy->ChangeStateMachine<EnState_LoseTarget>();  //����������Ԃɂ���B
		}
	}

	void TargetProbe::RouteEnd() {
		//�{���͂����ŃI�u�W�F�N�g�̒���`�������B
		m_probCount++;

		if (m_probCount >= m_numPorb) {
			m_probCount = 0;
			ChangeState();
		}
		else {  //�܂��J�E���g���߂��Ă��Ȃ�������B
			SetAstarRondomHideObject();
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