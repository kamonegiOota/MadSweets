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
		if (m_checkHideObj == nullptr) {
			return;
		}

		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		astar->RemoveNode(m_newNodeIndex);
	}


	void TargetProbe::SetAstarRondomHideObject() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			//�߂��̃I�u�W�F�N�g���烉���_���ɑ{���Ώۂ̃I�u�W�F�N�g��I���B
			auto hideObj = SearchHidden::SearchRandomHiddenObject(GetGameObject(), m_searchRange, m_checkHideObj);
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
		//�A�j���[�V�����̍Đ�
		auto animeCtrl = GetGameObject()->GetComponent<HandyAnimatorCtrl>(false);
		if (animeCtrl) {
			auto animator = animeCtrl->GetAnimator();
			animator->GetMemberRefarence().hideSearchTrigger.Fire();
		}

		//hideObject�̃R���C�_�[��off�ɂ��邱�ƂŔ��f
		SetHideObjCollisionUpdate(false);
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
		if (MyUtility::IsRayObstacle(GetGameObject(),m_checkHideObj, excluteObjs)) {
			m_moveFunc = nullptr;
		}

		auto veloComp = GetGameObject()->GetComponent<Velocity>(false);
		auto toVec = MyUtility::CalucToTargetVec(GetGameObject(), m_checkHideObj);

		if (veloComp) {
			auto velocity = veloComp->GetVelocity();
			auto force = UtilVelocity::CalucNearArriveFarSeek(velocity, toVec, GetVelocityMaxSpeed(), GetArriveNearRange());

			veloComp->SetForce(force);

			//�����̒���
			Rotation(veloComp->GetVelocity());
		}

		//�^�[�Q�b�g�̋߂��܂ŗ�����
		constexpr float NearRange = 2.0f;
		if (toVec.length() <= NearRange) {
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
		if (m_checkHideObj == nullptr) {
			return;
		}

		auto col = m_checkHideObj->GetComponent<Collision>(false);
		if (col) {
			if (col->GetUpdateActive() != isUpdate) {
				col->SetUpdateActive(isUpdate);
			}
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
			ChangeState<EnState_LoseTarget>();
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
		//Animator��ExitFunc�ŌĂяo������X�e�[�g���Ⴄ�ꍇ�͏��������Ȃ��悤�ɂ���B
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy) {
			//TargetProbe��ԂŖ��������珈�������Ȃ��B
			if (!enemy->IsEqualStateType<EnState_ProbTarget>()) {
				return;
			}
		}

		m_probCount++;  //���ׂ��J�E���g�̒ǉ�

		if (m_probCount >= m_numPorb) {  //�w��񐔒��ׂ���
			ChangeState<EnState_LoseTarget>();
		}
		else {  //�܂��J�E���g���߂��Ă��Ȃ�������B
			SetHideObjCollisionUpdate(true);
			SetAstarRondomHideObject();  //������x���ׂ�B
		}
	}

	void TargetProbe::ExitProbState() {
		RemoveNode();
		SetHideObjCollisionUpdate(true);
	}
}

//endbasecross