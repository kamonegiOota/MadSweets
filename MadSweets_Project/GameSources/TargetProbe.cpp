/*!
@file TargetProbe.cpp
@brief TargetProbe�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "TargetProbe.h"
#include "AstarCtrl.h"
#include "SearchHidden.h"
#include "BaseEnemy.h"
#include "EnState_LoseTarget.h"
#include "EnState_Plowling.h"

#include "Velocity.h"
#include "UtilVelocity.h"
#include "MyUtility.h"
#include "EnemyRotationCtrl.h"

#include "FixedBox.h"
#include "PlayerObject.h"
#include "HandyAnimator.h"
#include "EnState_ProbeTarget.h"
#include "HiddenComponent.h"
#include "EnState_Attack.h"

#include "I_Probe.h"
#include "WaitTimer.h"

#include "BaseAttack.h"
#include "TargetManager.h"

namespace basecross {

	using MyUtility = maru::MyUtility;

	void TargetProbe::AddNode(const Vec3& position) {
		return;
		vector<shared_ptr<GameObject>> obstacleObjs;
		vector<shared_ptr<GameObject>> excluteObjs;

		MyUtility::AddObjects<StageObject>(obstacleObjs); //��Q���̑Ώۂ�StageObject�ɂ���

		excluteObjs.push_back(GetGameObject()); //��������Q������Ȃ�
		MyUtility::AddObjects<PlayerObject>(excluteObjs);
		MyUtility::AddComponents<BaseEnemy>(excluteObjs);

		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			m_newNodeIndex = astar->AddNode(position, obstacleObjs, excluteObjs);
		}
	}

	void TargetProbe::RemoveNode() {
		return;
		if (m_checkHideObj.GetShard() == nullptr) {
			return;
		}

		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		astar->RemoveNode(m_newNodeIndex);
	}


	void TargetProbe::SetAstarRondomHideObject() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			//�߂��̃I�u�W�F�N�g���烉���_���ɑ{���Ώۂ̃I�u�W�F�N�g��I���B
			auto hideObj = SearchHidden::SearchRandomHiddenObject(GetGameObject(), m_searchRange, m_checkHideObj.GetShard());
			if (hideObj == nullptr) {  //�߂��ɉB���I�u�W�F�N�g������������
				return;
			}
			
			//�m�[�h�̒ǉ��ƍ폜
			RemoveNode();

			auto hidePosition = hideObj->GetComponent<Transform>()->GetPosition();
			hidePosition += hideObj->GetComponent<Transform>()->GetForword();
			AddNode(hidePosition);

			//���[�g�����X�^�[�g
			astar->SearchAstarStart(hideObj);

			//�T���Ă���I�u�W�F�N�g�̕ۑ�
			m_checkHideObj = hideObj;
			m_moveFunc = &TargetProbe::AstarMove;
		}
	}

	void TargetProbe::InvestigateHideObj() {
		auto probe = GetGameObject()->GetComponent<I_Probe>(false);
		if (probe) {
			probe->HideSearchAnimationStart();
		}

		//hideObject�̃R���C�_�[��off�ɂ��邱�ƂŔ��f
		SetHideObjCollisionUpdate(false);

		//hideObject��Player��������
		auto hide = m_checkHideObj->GetComponent<HiddenComponent>(false);
		if (hide->GetHideData().hideObject) {  //���ɉ��������Ă�����B
			auto targetManager = GetGameObject()->GetComponent<TargetManager>();
			auto target = targetManager->GetTarget();
			if (target) {
				auto attack = GetGameObject()->GetComponent<BaseAttack>(false);
				if (attack) {
					attack->Attack(target);
				}
			}
		}
	}

	void TargetProbe::RouteEnd() {
		//�{���͂����ŃI�u�W�F�N�g�̒���`�������B
		InvestigateHideObj();
		
		m_moveFunc = &TargetProbe::WaitInvestigateAnimationUpdateEnd;

		//���x��0�ɂ���B
		auto velocityComp = GetGameObject()->GetComponent<Velocity>(false);
		if (velocityComp) {
			velocityComp->Reset();
		}
	}

	void TargetProbe::WaitInvestigateAnimationUpdateEnd() {

	}

	void TargetProbe::TargetMove() {
		//�Ԃɏ�Q������������TargetMove�̏����𒆒f
		vector<std::shared_ptr<GameObject>> excluteObjs;
		MyUtility::AddComponents<BaseEnemy>(excluteObjs);
		MyUtility::AddObjects<PlayerObject>(excluteObjs);
		//MyUtility::AddComponents<HiddenComponent>(excluteObjs);
		if (MyUtility::IsRayObstacle(GetGameObject(),m_checkHideObj.GetShard(), excluteObjs)) {
			LostTimerStart();
		}
		else {
			LostTimerCancel();
		}

		auto veloComp = GetGameObject()->GetComponent<Velocity>(false);
		auto toVec = MyUtility::CalucToTargetVec(GetGameObject(), m_checkHideObj.GetShard());

		if (veloComp) {
			auto velocity = veloComp->GetVelocity();
			auto force = UtilVelocity::CalucNearArriveFarSeek(velocity, toVec, GetVelocityMaxSpeed(), GetArriveNearRange());

			veloComp->SetForce(force);

			//�����̒���
			Rotation(veloComp->GetVelocity());
		}

		//�^�[�Q�b�g�̋߂��܂ŗ�����
		constexpr float NearRange = 1.5f;
		if (toVec.length() <= NearRange) {
			LostTimerCancel();
			RouteEnd();
		}
	}

	void TargetProbe::AstarMove() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			astar->UpdateVelocityMove(GetVelocityMaxSpeed(), GetArriveNearRange());

			//�Ώۂ̏�Q�����肪�Ȃ��Ȃ�����ł����������H
			if (astar->IsRouteEnd()) {
				m_moveFunc = &TargetProbe::TargetMove;
			}
		}
	}

	void TargetProbe::Rotation(const Vec3& direct) {
		auto rotation = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
		if (rotation) {
			rotation->SetDirect(direct);
		}
	}

	void TargetProbe::ResetProbe() {
		m_probCount = 0;
		m_moveFunc = nullptr;
		m_checkHideObj = nullptr;
	}

	void TargetProbe::SetHideObjCollisionUpdate(const bool isUpdate) {
		if (m_checkHideObj.GetShard() == nullptr) {
			return;
		}

		auto col = m_checkHideObj->GetComponent<Collision>(false);
		if (col) {
			if (col->GetUpdateActive() != isUpdate) {
				col->SetUpdateActive(isUpdate);
			}
		}
	}

	void TargetProbe::ChangeEndProbeState() {
		auto probe = GetGameObject()->GetComponent<I_Probe>(false);
		if (probe) {
			probe->EndProbe();
		}
	}

	void TargetProbe::LostTimerStart() {
		auto waitTimer = GetGameObject()->GetComponent<WaitTimer>(false);
		if (waitTimer) {
			if (waitTimer->IsWait(GetThis<TargetProbe>())) {  //�ҋ@��ԂȂ珈�������Ȃ��B
				return;
			}

			waitTimer->AddTimer(GetThis<TargetProbe>(), m_lostSeekTime, [this]() { m_moveFunc = nullptr; });
		}
	}

	void TargetProbe::LostTimerCancel() {
		auto waitTimer = GetGameObject()->GetComponent<WaitTimer>(false);
		if (waitTimer) {
			waitTimer->AbsoluteEndTimer(GetThis<TargetProbe>(), false);
		}
	}

	void TargetProbe::OnCreate() {
		SetUpdateActive(false);
	}

	void TargetProbe::OnUpdate() {
		if (m_moveFunc) {
			m_moveFunc(*this);
		}
		else {
			SetHideObjCollisionUpdate(true);
			ChangeEndProbeState();  //�X�e�[�g�}�V���ύX���ɕύX
		}
	}

	void TargetProbe::StartProb() {
		ResetProbe();
		SetAstarRondomHideObject();
	}

	void TargetProbe::StartProb(const shared_ptr<GameObject>& target) {
		ResetProbe();
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			astar->SearchAstarStart(target);
			m_checkHideObj = target;
			m_moveFunc = &TargetProbe::TargetMove;
		}
	}

	void TargetProbe::EndInvestigateHideAnimation() {
		if (GetUpdateActive() == false) {
			return;
		}

		m_probCount++;  //���ׂ��J�E���g�̒ǉ�

		if (m_probCount >= m_numPorb) {  //�w��񐔒��ׂ���
			ChangeEndProbeState();
		}
		else {  //�܂��J�E���g���߂��Ă��Ȃ�������B
			SetHideObjCollisionUpdate(true);
			SetAstarRondomHideObject();  //������x���ׂ�B
		}
	}

	void TargetProbe::ExitProbState() {
		RemoveNode();
		SetHideObjCollisionUpdate(true);
		LostTimerCancel();
	}
}

//endbasecross