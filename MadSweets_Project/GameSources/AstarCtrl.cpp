/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "AstarCtrl.h"
#include "MTestEnemyObject.h"
#include "MTestBox.h"
#include "CalucEscapeRoute.h"

#include "Velocity.h"
#include "UtilVelocity.h"
#include "EnemyRotationCtrl.h"

namespace basecross {

	Vec3 AstarCtrl::CalucMoveVec() {
		auto nodePos = m_astar.CalucTargetNode(GetGameObject());
		auto toVec = nodePos - transform->GetPosition();

		return toVec;
	}

	void AstarCtrl::UpdateMove() {
		if (m_astar.IsRouteEnd()) { //ルートの最後まで来たら処理を止める。
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();

		auto nodePos = m_astar.CalucTargetNode(GetGameObject());
		auto toVec = nodePos - transform->GetPosition();

		auto pos = transform->GetPosition();
		pos += toVec.GetNormalized() * delta * m_speed;
		transform->SetPosition(pos);
	}

	void AstarCtrl::UpdateVelocityMove(const float& maxSpeed, const float& nearRange) {
		if (m_astar.IsRouteEnd()) {
			return;
		}

		auto moveVec = CalucMoveVec();

		//スピードの加算
		auto veloComp = GetGameObject()->GetComponent<Velocity>(false);
		if (veloComp) {
			auto velocity = veloComp->GetVelocity();
			auto force = UtilVelocity::CalucNearArriveFarSeek(velocity, moveVec, maxSpeed, nearRange);
			veloComp->SetForce(force);
		}

		//向きの調整
		auto rotation = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
		if (rotation) {
			rotation->SetDirect(veloComp->GetVelocity());
		}
	}

	void AstarCtrl::OnCreate() {

	}

	void AstarCtrl::SearchAstarStart(const std::shared_ptr<GameObject>& target, const bool isCreateNode) {
		//if (isCreateNode) {
		//	m_astar.AddNode();
		//}
		SearchAstarStart(target->GetComponent<Transform>()->GetPosition(), isCreateNode);
	}

	void AstarCtrl::SearchAstarStart(const Vec3& targetPos, const bool isCreateNode) {
		if (isCreateNode) {
			m_astar.AddNode(targetPos);
		}
		m_astar.SearchAstarStart(GetGameObject(), targetPos);
	}

	void AstarCtrl::SearchAstarForecastStart(const std::shared_ptr<GameObject>& target) {
		m_astar.SearchAstarForecastStart(GetGameObject(),target);
	}

	void AstarCtrl::SearchAstarEscapeStart(const std::shared_ptr<GameObject>& target) {
		auto targetNode = CalucEscapeRoute::CalucRoute(m_astar,GetGameObject(),target);

		m_astar.SearchAstarStart(GetGameObject(),targetNode.GetPosition());
	}

	void AstarCtrl::SearchAstarEscapeNextRoute(const std::shared_ptr<GameObject>& target) {
		auto targetNode = CalucEscapeRoute::CalucNextRoute(m_astar,GetGameObject(),target);

		m_astar.SearchAstarStart(GetGameObject(), targetNode.GetPosition());
	}

	int AstarCtrl::AddNode(const Vec3& position,
		const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs) 
	{
		return m_astar.AddNode(position, obstacleObjs, excluteObjs);
	}

	void AstarCtrl::RemoveNode(const int& index) {
		m_astar.RemoveNode(index);
	}
}

//endbasecross