/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
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

	void ChaseAstarMove::Rotation(const Vec3& moveVec) {
		auto rotCtrl = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
		if (rotCtrl) {
			rotCtrl->SetDirect(moveVec);
		}
	}

	void ChaseAstarMove::CalucRoute(const std::shared_ptr<GameObject>& target) {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			//�ړI�̃|�W�V�������擾
			m_targetPosition = astar->CalucTargetNearNodePosition(target);
		}
	}

	void ChaseAstarMove::CalucNextRoute(const std::shared_ptr<GameObject>& target) {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			auto node = astar->CalucMyNodeToTargetNearNode(target);
			m_targetPosition = node.GetPosition();
		}
	}

	void ChaseAstarMove::OnStart() {
		//Velocity���g���Ƃ��̏����l��ݒ�
		BaseUseVelocity::SetVelocityMaxSpeed(3.0f);
		BaseUseVelocity::SetArriveNearRange(15.0f);
	}

	void ChaseAstarMove::Move() {
		auto selfPosition = GetGameObject()->GetComponent<Transform>()->GetPosition();
		auto moveVec = m_targetPosition - selfPosition;

		//�X�s�[�h�̉��Z
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

	void ChaseAstarMove::LostTarget(const std::shared_ptr<GameObject>& target) {
		CalucRoute(target);
		//���������ꏊ�̋L�^
		m_target = target;
		m_isProbeEnd = false;
		m_numLostChaseElapsed = m_numLostChase;
	}

	void ChaseAstarMove::NextRoute() {
		//�^�[�Q�b�g�����E�͈̔͂ɂ��邩�ǂ���
		const auto& target = m_target.GetShard();
		vector<shared_ptr<GameObject>> excluteObjs;
		MyUtility::AddComponents<BaseEnemy>(excluteObjs);
		excluteObjs.push_back(target);

		if (!MyUtility::IsRayObstacle(GetGameObject(), target, excluteObjs)) {
			//���E���ɂ���Ȃ�
			m_targetPosition = target->GetComponent<Transform>()->GetPosition();
			ResetNumLostChaseElapsed();
		}
		else {  //���E�̊O�ɂ�����
			CalucNextRoute(target);

			m_numLostChaseElapsed--;
			if (m_numLostChaseElapsed < 0) {
				m_isProbeEnd = true;
				ResetNumLostChaseElapsed();
			}
		}

		//�f�o�b�O-------------------------------------------------------
		DebugObject::sm_wss << L"numLost: ";
		DebugObject::AddValue(m_numLostChaseElapsed, true);
	}

}

//endbasecross