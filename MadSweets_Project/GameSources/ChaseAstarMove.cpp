/*!
@file ChaseAstarMove.cpp
@brief ChaseAstarMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "ChaseAstarMove.h"
#include "TargetChase.h"
#include "Velocity.h"
#include "UtilVelocity.h"
#include "EnemyRotationCtrl.h"

#include "MyUtility.h"
#include "BaseEnemy.h"
#include "TactileCtrl.h"

#include "WaitTimer.h"

namespace basecross {

	using MyUtility = maru::MyUtility;

	void ChaseAstarMove::ResetNumLostChaseElapsed() {
		m_numLostChaseElapsed = m_numLostChase;
	}

	bool ChaseAstarMove::IsRouteEnd() {
		auto selfPosition = GetGameObject()->GetComponent<Transform>()->GetPosition();
		auto toVec = m_targetPosition - selfPosition;
		if (toVec.length() <= m_targetNearRange) {
			return true;
		}

		return false;
	}

	bool ChaseAstarMove::IsRayObstacle(const std::shared_ptr<GameObject>& target) {
		vector<shared_ptr<GameObject>> excluteObjs;
		excluteObjs.push_back(target);
		return IsRayObstacle(target->GetComponent<Transform>()->GetPosition());
	}

	bool ChaseAstarMove::IsRayObstacle(const Vec3& targetPosition, vector<shared_ptr<GameObject>>& excluteObjs) {
		MyUtility::AddComponents<BaseEnemy>(excluteObjs);
		excluteObjs.push_back(GetGameObject());
		excluteObjs.push_back(m_target.GetShard());

		auto selfPosition = GetGameObject()->GetComponent<Transform>()->GetPosition();
		if (MyUtility::IsRayObstacle(selfPosition, targetPosition, excluteObjs)) {
			return true;
		}
		else {
			return false;
		}
	}

	void ChaseAstarMove::Rotation(const Vec3& moveVec) {
		auto rotCtrl = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
		if (rotCtrl) {
			rotCtrl->SetDirect(moveVec);
		}
	}

	void ChaseAstarMove::CalcuRoute(const std::shared_ptr<GameObject>& target) {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			//目的のポジションを取得
			m_targetPosition = astar->CalucTargetNearNodePosition(target);
		}
	}

	void ChaseAstarMove::CalcuNextRoute(const std::shared_ptr<GameObject>& target) {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			auto node = astar->CalucMyNodeToTargetNearNode(target);
			m_targetPosition = node->GetPosition();
		}
	}

	Vec3 ChaseAstarMove::CalcuMoveForce(const std::shared_ptr<GameObject>& target) {
		auto selfPosition = GetGameObject()->GetComponent<Transform>()->GetPosition();
		auto moveVec = m_targetPosition - selfPosition;

		//スピードの加算
		auto velocityComp = GetGameObject()->GetComponent<Velocity>(false);
		auto velocity = velocityComp->GetVelocity();
		auto force = UtilVelocity::CalucNearArriveFarSeek(velocity, moveVec, GetVelocityMaxSpeed(), GetArriveNearRange());

		return force;
	}

	void ChaseAstarMove::LostTimerStart() {
		auto waitTimer = GetGameObject()->GetComponent<WaitTimer>(false);
		if (waitTimer) {
			if (waitTimer->IsWait(GetThis<ChaseAstarMove>())) {  //待機状態なら処理をしない。
				return;
			}
			
			waitTimer->AddTimer(GetThis<ChaseAstarMove>(), m_lostSeekTime, [this](){ NextRoute(); });
		}
	}

	void ChaseAstarMove::LostTimerCancel() {
		auto waitTimer = GetGameObject()->GetComponent<WaitTimer>(false);
		if (waitTimer) {
			waitTimer->AbsoluteEndTimer(GetThis<ChaseAstarMove>(), false);
		}
	}

	void ChaseAstarMove::OnStart() {
		//Velocityを使うときの初期値を設定
		BaseUseVelocity::SetVelocityMaxSpeed(3.0f);
		BaseUseVelocity::SetArriveNearRange(15.0f);
	}

	void ChaseAstarMove::Move() {
		//スピードの加算
		auto velocityComp = GetGameObject()->GetComponent<Velocity>(false);
		if (velocityComp) {
			auto force = CalcuMoveForce(m_target.GetShard());
			velocityComp->AddForce(force);

			Rotation(velocityComp->GetVelocity());
		}

		//見失ったら
		if (IsRayObstacle(m_targetPosition)) {
			LostTimerStart();   //ターゲットのロストカウントダウン開始
		}
		else {
			LostTimerCancel();  //ターゲットのロスト解除
		}

		if (IsRouteEnd()) {
			NextRoute();
		}
	}

	void ChaseAstarMove::LostTarget(const std::shared_ptr<GameObject>& target) {
		CalcuRoute(target);
		//見失った場所の記録
		m_target = target;
		m_isProbeEnd = false;
		m_numLostChaseElapsed = m_numLostChase;
	}

	void ChaseAstarMove::NextRoute() {
		//ターゲットが視界の範囲にいるかどうか
		const auto& target = m_target.GetShard();

		if (!IsRayObstacle(target)) {
			//視界内にいるなら
			m_targetPosition = target->GetComponent<Transform>()->GetPosition();
			ResetNumLostChaseElapsed();
		}
		else {  //視界の外にいたら
			CalcuNextRoute(target);

			m_numLostChaseElapsed--;
			if (m_numLostChaseElapsed < 0) {
				m_isProbeEnd = true;
				ResetNumLostChaseElapsed();
			}
		}

		//デバッグ-------------------------------------------------------
		DebugObject::sm_wss << L"numLost: ";
		DebugObject::AddValue(m_numLostChaseElapsed, true);
	}

}

//endbasecross