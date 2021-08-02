/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
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
		if (m_astar.IsRouteEnd()) { //���[�g�̍Ō�܂ŗ����珈�����~�߂�B
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

		//�X�s�[�h�̉��Z
		auto veloComp = GetGameObject()->GetComponent<Velocity>(false);
		if (veloComp) {
			auto velocity = veloComp->GetVelocity();
			auto force = UtilVelocity::CalucNearArriveFarSeek(velocity, moveVec, maxSpeed, nearRange);
			veloComp->SetForce(force);
		}

		//�����̒���
		auto rotation = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
		if (rotation) {
			rotation->SetDirect(veloComp->GetVelocity());
		}
	}

	void AstarCtrl::OnCreate() {

	}

	void AstarCtrl::SearchAstarStart(const std::shared_ptr<GameObject>& target) {
		m_astar.SearchAstarStart(GetGameObject(), target);
	}

	void AstarCtrl::SearchAstarStart(const Vec3& targetPos) {
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
}

//endbasecross