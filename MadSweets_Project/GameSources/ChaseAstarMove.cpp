/*!
@file ChaseAstarMove.cpp
@brief ChaseAstarMove�Ȃǎ���
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
			//�ړI�̃|�W�V�������擾
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

		//�X�s�[�h�̉��Z
		auto velocityComp = GetGameObject()->GetComponent<Velocity>(false);
		auto velocity = velocityComp->GetVelocity();
		auto force = UtilVelocity::CalucNearArriveFarSeek(velocity, moveVec, GetVelocityMaxSpeed(), GetArriveNearRange());

		return force;
	}

	void ChaseAstarMove::LostTimerStart() {
		auto waitTimer = GetGameObject()->GetComponent<WaitTimer>(false);
		if (waitTimer) {
			if (waitTimer->IsWait(GetThis<ChaseAstarMove>())) {  //�ҋ@��ԂȂ珈�������Ȃ��B
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
		//Velocity���g���Ƃ��̏����l��ݒ�
		BaseUseVelocity::SetVelocityMaxSpeed(3.0f);
		BaseUseVelocity::SetArriveNearRange(15.0f);
	}

	void ChaseAstarMove::Move() {
		//�X�s�[�h�̉��Z
		auto velocityComp = GetGameObject()->GetComponent<Velocity>(false);
		if (velocityComp) {
			auto force = CalcuMoveForce(m_target.GetShard());
			velocityComp->AddForce(force);

			Rotation(velocityComp->GetVelocity());
		}

		//����������
		if (IsRayObstacle(m_targetPosition)) {
			LostTimerStart();   //�^�[�Q�b�g�̃��X�g�J�E���g�_�E���J�n
		}
		else {
			LostTimerCancel();  //�^�[�Q�b�g�̃��X�g����
		}

		if (IsRouteEnd()) {
			NextRoute();
		}
	}

	void ChaseAstarMove::LostTarget(const std::shared_ptr<GameObject>& target) {
		CalcuRoute(target);
		//���������ꏊ�̋L�^
		m_target = target;
		m_isProbeEnd = false;
		m_numLostChaseElapsed = m_numLostChase;
	}

	void ChaseAstarMove::NextRoute() {
		//�^�[�Q�b�g�����E�͈̔͂ɂ��邩�ǂ���
		const auto& target = m_target.GetShard();

		if (!IsRayObstacle(target)) {
			//���E���ɂ���Ȃ�
			m_targetPosition = target->GetComponent<Transform>()->GetPosition();
			ResetNumLostChaseElapsed();
		}
		else {  //���E�̊O�ɂ�����
			CalcuNextRoute(target);

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