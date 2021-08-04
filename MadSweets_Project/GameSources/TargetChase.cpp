/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "TargetChase.h"
#include "Velocity.h"
#include "UtilVelocity.h"
#include "MyUtility.h"

#include "EyeSearchRange.h"
#include "EnemyRotationCtrl.h"
#include "AstarCtrl.h"
#include "I_Chase.h"
#include "DebugObject.h"

#include "ProbeAstarMove.h"

namespace basecross {

	TargetChase::TargetChase(const std::shared_ptr<GameObject>& objPtr):
		TargetChase(objPtr,nullptr)
	{}

	TargetChase::TargetChase(const std::shared_ptr<GameObject>& objPtr,
		const std::shared_ptr<GameObject>& target
	) :
		TargetChase(objPtr,target,2.0f)
	{}

	TargetChase::TargetChase(const std::shared_ptr<GameObject>& objPtr,
		const std::shared_ptr<GameObject>& target,
		const float& speed
	):
		Component(objPtr),
		m_target(target),
		m_speed(speed)
	{}


	void TargetChase::LookMove() {
		auto delta = App::GetApp()->GetElapsedTime();
		auto velocity = GetGameObject()->GetComponent<Velocity>(false);
		if (!velocity) {
			return;
		}

		auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), m_target);
		
		auto maxSpeed = 4.0f;  //�����I�Ƀ����o�ϐ���
		auto velo = velocity->GetVelocity();
		auto force = UtilVelocity::CalucSeekVec(velo, toVec, maxSpeed);

		velocity->AddForce(toVec);

		Rotation(velo);

		LostCheck();
	}

	void TargetChase::LostCheck() {
		//���E�ɓ����Ă��邩�ǂ����𔻒f
		auto obj = GetGameObject();
		auto eyeRange = obj->GetComponent<EyeSearchRange>(false);
		if (eyeRange == nullptr) {
			return;
		}

		//���E�O�Ȃ�Astar�𗘗p���Ēǂ�������B
		if (!eyeRange->IsLookTarget(m_target)) {
			auto probe = GetGameObject()->GetComponent<ProbeAstarMove>(false);
			if (probe) {
				probe->CalucRoute(m_target);
				m_updateFunc = &TargetChase::LostMove;

				//�e�X�g����
				auto draw = obj->GetComponent<BcBaseDraw>(false);
				if (draw) {
					draw->SetDiffuse(Col4(1.0f, 0.0f, 1.0f, 1.0f));
				}
			}

		}
	}

	void TargetChase::LostMove() {
		auto probe = GetGameObject()->GetComponent<ProbeAstarMove>(false);
		if (probe) {
			probe->Move();
			if (probe->IsRouteEnd()) {
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

		if (eyeRange->IsLookTarget(m_target)) {  //�ꕔ�̃I�u�W�F�N�g����Q���Ƃ��Ĉ���Ȃ��悤�ɂ���
			m_updateFunc = &TargetChase::LookMove;

			//�e�X�g����
			auto draw = obj->GetComponent<BcBaseDraw>(false);
			if (draw) {
				draw->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
			}
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
			chase->ChangeTargetLostState(m_target);
		}
	}

	void TargetChase::OnCreate() {
		m_updateFunc = &TargetChase::LookMove;
	}

	void TargetChase::OnUpdate() {
		if (m_target == nullptr) {  //�^�[�Q�b�g���Ǐ]
			return;
		}

		if (m_updateFunc) {
			m_updateFunc(*this);
		}
	}

}

//endbasecross