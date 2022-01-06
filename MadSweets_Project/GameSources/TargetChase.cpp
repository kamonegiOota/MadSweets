/*!
@file TargetChase.cpp
@brief TargetChase�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "TargetChase.h"
#include "TargetProbe.h"
#include "Velocity.h"
#include "UtilVelocity.h"
#include "MyUtility.h"

#include "EyeSearchRange.h"
#include "EnemyRotationCtrl.h"
#include "AstarCtrl.h"
#include "I_Chase.h"
#include "DebugObject.h"

#include "ChaseAstarMove.h"
#include "HiddenComponent.h"

namespace basecross {

	//TargetChase::TargetChase(const std::shared_ptr<GameObject>& objPtr):
	//	TargetChase(objPtr,nullptr)
	//{}

	TargetChase::TargetChase(const std::shared_ptr<GameObject>& objPtr) :
		TargetChase(objPtr, 10.0f)
	{}

	TargetChase::TargetChase(const std::shared_ptr<GameObject>& objPtr, const float& speed)
		:Component(objPtr), m_maxSpeed(speed)
	{}

	bool TargetChase::TargetEyeRangeHide() {
		auto obj = GetGameObject();
		auto eyeRange = obj->GetComponent<EyeSearchRange>(false);

		//���E�̐�ɉB���I�u�W�F�N�g�������Ă�����player���B��Ă����炻����^�[�Q�b�g�ɂ���B
		auto hides = maru::MyUtility::GetComponents<HiddenComponent>();
		for (auto& hide : hides) {
			if (eyeRange->IsInEyeRange(hide->GetGameObject())) {  //�{����EyeRange�Ŕ��f
				auto toVec = maru::MyUtility::CalucToTargetVec(m_target.GetShard(), hide->GetGameObject());
				if (toVec.length() <= 0.01f) {  //����Ȃ��߂��Ƃ������Ƃ͉B�ꂽ�Ƃ������B
					m_isEnd = true;
					ChangeStateMachine();  //�X�e�[�g�̕ύX
					//�^�[�Q�b�g�����ڂ̑O�ɉB�ꂽ�I�u�W�F�N�g�ɂ���B
					GetGameObject()->GetComponent<TargetProbe>()->StartProb(hide->GetGameObject());
					return true;
				}
			}
		}

		return false;
	}

	void TargetChase::LostTarget() {
		if (m_chaseMode == ChaseMode::Lost) {  //���X�g��ԂȂ珈�������Ȃ��B
			return;
		}
		m_chaseMode = ChaseMode::Lost;

		//�����������̏����B
		auto obj = GetGameObject();
		auto eyeRange = obj->GetComponent<EyeSearchRange>(false);

		//���E�̐�ɉB���I�u�W�F�N�g�������Ă�����player���B��Ă����炻����^�[�Q�b�g�ɂ���B
		auto isTargetHide = TargetEyeRangeHide();
		if (isTargetHide) {  //�B�ꂽ�炻�̌�̏��������Ȃ��B
			return;
		}

		auto cahseAstarMove = GetGameObject()->GetComponent<ChaseAstarMove>(false);
		if (cahseAstarMove) {
			//�ʏ�T��
			cahseAstarMove->LostTarget(m_target.GetShard());
			m_updateFunc = &TargetChase::LostMove;
		}
	}

	void TargetChase::FindTarget() {
		m_updateFunc = &TargetChase::LookMove;

		//�e�X�g����
		auto draw = GetGameObject()->GetComponent<BcBaseDraw>(false);
		if (draw) {
			draw->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		}

		m_chaseMode = ChaseMode::Look;
	}

	void TargetChase::LookMove() {
		auto delta = App::GetApp()->GetElapsedTime();
		auto velocity = GetGameObject()->GetComponent<Velocity>(false);
		if (!velocity) {
			return;
		}

		auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), m_target.GetShard());
		
		auto velo = velocity->GetVelocity();
		auto force = UtilVelocity::CalucSeekVec(velo, toVec, m_maxSpeed);

		velocity->AddForce(force);

		Rotation(velocity->GetVelocity());

		LookCheck();
	}

	void TargetChase::LostMove() {
		auto cahseAstarMove = GetGameObject()->GetComponent<ChaseAstarMove>(false);
		if (cahseAstarMove) {
			cahseAstarMove->Move();
			if (cahseAstarMove->IsProbeEnd()) {
				m_isEnd = true;
				ChangeStateMachine();
				return;
			}
		}

		LookCheck();
	}

	void TargetChase::LookCheck() {
		//���E�ɓ����Ă��邩�ǂ����𔻒f
		auto obj = GetGameObject();
		auto eyeRange = obj->GetComponent<EyeSearchRange>(false);
		if (eyeRange == nullptr) {
			return;
		}

		//���E�O�ɂ��邩�ǂ����H
		if (eyeRange->IsLookTarget(m_target.GetShard())) {
			FindTarget();
		}
		else{
			//���������Ȃ�Astar�𗘗p���Ēǂ�������B
			LostTarget();
		}
	}

	void TargetChase::Rotation(const Vec3& moveVec) {
		auto rotCtrl = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
		if (rotCtrl) {
			rotCtrl->SetDirect(moveVec);
		}
	}

	void TargetChase::ChangeStateMachine() {
		auto chase = GetGameObject()->GetComponent<I_Chase>(false);
		if (chase) {
			chase->EndChase();
		}
	}

	void TargetChase::OnCreate() {
		m_updateFunc = &TargetChase::LookMove;
	}

	void TargetChase::OnUpdate() {
		if (m_target.GetShard() == nullptr) {  //�^�[�Q�b�g���Ǐ]
			return;
		}

		if (m_updateFunc) {
			m_updateFunc(*this);
		}
	}
}

//endbasecross