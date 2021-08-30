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

	void TargetProbe::AddNode(const Vec3& position) {
		//return;
		vector<shared_ptr<GameObject>> obstacleObjs;
		vector<shared_ptr<GameObject>> excluteObjs;

		MyUtility::AddObjects<StageObject>(obstacleObjs); //��Q���̑Ώۂ�StageObject�ɂ���
		excluteObjs.push_back(GetGameObject()); //��������Q������Ȃ�
		MyUtility::AddObjects<PlayerObject>(excluteObjs);
		MyUtility::AddComponents<BaseEnemy>(excluteObjs);

		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		m_newNodeIndex = astar->AddNode(position, obstacleObjs, excluteObjs);
	}

	void TargetProbe::RemoveNode() {
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

			DebugObject::sm_wss << endl << L"RandomHide" <<  endl;

			if (hideObj == nullptr) {  //�߂��ɉB���I�u�W�F�N�g������������
				return;
			}
			
			//�m�[�h�̒ǉ��ƍ폜
			RemoveNode();
			AddNode(hideObj->GetComponent<Transform>()->GetPosition()); 

			astar->SearchAstarStart(hideObj);
			m_checkHideObj = hideObj;
			m_moveFunc = &TargetProbe::AstarMove;
		}
	}

	void TargetProbe::InvestigateHideObj() {
		//�A�j���[�V�����̍Đ�s
		auto animeCtrl = GetGameObject()->GetComponent<HandyAnimatorCtrl>(false);
		if (animeCtrl) {
			auto animator = animeCtrl->GetAnimator();
			animator->GetMemberRefarence().hideSearchTrigger.Fire();
		}

		//�G�������ł��邩�ǂ���?
		//hideObject�̃R���C�_�[��off�ɂ��邱�ƂŔ��f
		SetHideObjCollisionUpdate(false);

		return;
		//���݂͉��Ŕ��f���Ă���B
		auto hideComp = m_checkHideObj->GetComponent<HiddenComponent>(false);
		if (hideComp) {
			auto pos = hideComp->GetHideData().hideWorldPosition;
			auto toVec = m_target->GetComponent<Transform>()->GetPosition() - pos;
			if (toVec.length() <= 0.01f) {
				//ChangeState<EnState_Attack>(m_target);
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
		auto veloComp = GetGameObject()->GetComponent<Velocity>(false);
		auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), m_checkHideObj);

		if (veloComp) {
			auto velocity = veloComp->GetVelocity();
			auto force = UtilVelocity::CalucNearArriveFarSeek(velocity, toVec, GetVelocityMaxSpeed(), GetArriveNearRange());

			veloComp->SetForce(force);

			//�����̒���
			auto rotation = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
			if (rotation) {
				rotation->SetDirect(veloComp->GetVelocity());
			}
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
				//RouteEnd();
			}
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
		//m_moveFunc = nullptr;

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
		//�����o�O��������悤�Ȃ�A�������Update�ŃA�j���[�V�����̏I�����Ď�����悤�ɂ���B
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy) {
			//TargetProbe��ԂŖ��������珈�������Ȃ��B
			if (!enemy->IsEqualStateType<EnState_ProbTarget>()) {
				return;
			}
		}

		m_probCount++;

		if (m_probCount >= m_numPorb) {  //�w��񐔒��ׂ���B
			m_moveFunc = nullptr;
			//ChangeState<EnState_LoseTarget>();
		}
		else {  //�܂��J�E���g���߂��Ă��Ȃ�������B
			SetHideObjCollisionUpdate(true);
			SetAstarRondomHideObject();  //������x���ׂ�B
		}
	}

	void TargetProbe::ExitProbState() {
		//SetHideObjCollisionUpdate(true);
		RemoveNode();
	}
}

//endbasecross