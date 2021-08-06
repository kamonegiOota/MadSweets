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

#include "Velocity.h"
#include "UtilVelocity.h"
#include "MyUtility.h"
#include "EnemyRotationCtrl.h"

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

			//StartProb(hideObj);
			astar->SearchAstarStart(hideObj);
			m_checkHideObj = hideObj;
			m_moveFunc = &TargetProbe::AstarMove;
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

	void TargetProbe::TargetMove() {
		auto veloComp = GetGameObject()->GetComponent<Velocity>();
		auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), m_checkHideObj);

		if (veloComp) {
			auto velocity = veloComp->GetVelocity();
			auto force = UtilVelocity::CalucNearArriveFarSeek(velocity, toVec, GetVelocityMaxSpeed(), GetArriveNearRange());

			veloComp->SetForce(force);

			//向きの調整
			auto rotation = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
			if (rotation) {
				rotation->SetDirect(veloComp->GetVelocity());
			}
		}

		//ターゲットの近くまで来たら
		constexpr float NearRange = 2.0f;
		if (toVec.length() <= NearRange) {
			RouteEnd();
		}
	}

	void TargetProbe::AstarMove() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>();
		if (astar) {
			astar->UpdateVelocityMove(GetVelocityMaxSpeed(), GetArriveNearRange());

			//対象の障害物判定がなくなったらでもいいかも？
			if (astar->IsRouteEnd()) {
				m_moveFunc = &TargetProbe::TargetMove;
				//RouteEnd();
			}
		}
	}

	void TargetProbe::ResetProbe() {
		m_probCount = 0;
		m_checkHideObj = nullptr;
	}

	void TargetProbe::OnCreate() {
		SetUpdateActive(false);
	}

	void TargetProbe::OnUpdate() {
		if (m_moveFunc) {
			m_moveFunc(*this);
		}
	}

	void TargetProbe::StartProb() {
		ResetProbe();
		SetAstarRondomHideObject();
	}

	void TargetProbe::StartProb(const shared_ptr<GameObject>& target) {
		ResetProbe();
		auto astar = GetGameObject()->GetComponent<AstarCtrl>();
		if (astar) {
			astar->SearchAstarStart(target);
			m_checkHideObj = target;
			m_moveFunc = &TargetProbe::TargetMove;
		}
	}

}

//endbasecross