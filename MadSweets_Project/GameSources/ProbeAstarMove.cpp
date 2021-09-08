/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "ProbeAstarMove.h"
#include "TargetChase.h"
#include "Velocity.h"
#include "UtilVelocity.h"
#include "EnemyRotationCtrl.h"

#include "MyUtility.h"
#include "BaseEnemy.h"
#include "TactileCtrl.h"

namespace basecross {

	using MyUtility = maru::MyUtility;

	void ProbeAstarMove::ResetNumLostChaseElapsed() {
		m_numLostChaseElapsed = m_numLostChase;
	}

	bool ProbeAstarMove::IsRouteEnd() {
		auto selfPosition = GetGameObject()->GetComponent<Transform>()->GetPosition();
		auto toVec = m_targetPosition - selfPosition;
		if (toVec.length() <= m_targetNearRange) {
			return true;
		}

		return false;
	}

	void ProbeAstarMove::Rotation(const Vec3& moveVec) {
		auto rotCtrl = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
		if (rotCtrl) {
			rotCtrl->SetDirect(moveVec);
		}
	}

	void ProbeAstarMove::ChangeTargetChase() {
		auto chase = GetGameObject()->GetComponent<TargetChase>();
		if (chase) {
			chase->SetUpdateActive(true);
			SetUpdateActive(false);
		}
	}

	void ProbeAstarMove::CalucRoute(const std::shared_ptr<GameObject>& target) {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			//目的のポジションを取得
			m_targetPosition = astar->CalucTargetNearNodePosition(target);
		}
	}

	void ProbeAstarMove::CalucNextRoute(const std::shared_ptr<GameObject>& target) {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			auto node = astar->CalucMyNodeToTargetNearNode(target);
			m_targetPosition = node.GetPosition();
		}
	}

	void ProbeAstarMove::OnStart() {
		//Velocityを使うときの初期値を設定
		BaseUseVelocity::SetVelocityMaxSpeed(3.0f);
		BaseUseVelocity::SetArriveNearRange(15.0f);
	}

	void ProbeAstarMove::Move() {
		auto selfPosition = GetGameObject()->GetComponent<Transform>()->GetPosition();
		auto moveVec = m_targetPosition - selfPosition;

		//スピードの加算
		auto velocityComp = GetGameObject()->GetComponent<Velocity>(false);
		if (velocityComp) {
			auto velocity = velocityComp->GetVelocity();
			auto force = UtilVelocity::CalucNearArriveFarSeek(velocity, moveVec, GetVelocityMaxSpeed(), GetArriveNearRange());
			velocityComp->SetForce(force);

			Rotation(velocity);
		}

		if (IsRouteEnd()) {
			NextRoute();
		}
	}

	void ProbeAstarMove::LostTarget(const std::shared_ptr<GameObject>& target) {
		CalucRoute(target);
		//見失った場所の記録
		m_target = target;
		m_isProbeEnd = false;
		m_numLostChaseElapsed = m_numLostChase;
	}

	void ProbeAstarMove::NextRoute() {
		//ターゲットが視界の範囲にいるかどうか
		const auto& target = m_target.GetShard();
		vector<shared_ptr<GameObject>> excluteObjs;
		MyUtility::AddComponents<BaseEnemy>(excluteObjs);
		excluteObjs.push_back(target);

		if (!MyUtility::IsRayObstacle(GetGameObject(), target, excluteObjs)) {
			//視界内にいるなら
			m_targetPosition = target->GetComponent<Transform>()->GetPosition();
			ResetNumLostChaseElapsed();
		}
		else {  //視界の外にいたら
			CalucNextRoute(target);

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