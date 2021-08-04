/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
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
		
		auto maxSpeed = 4.0f;  //将来的にメンバ変数化
		auto velo = velocity->GetVelocity();
		auto force = UtilVelocity::CalucSeekVec(velo, toVec, maxSpeed);

		velocity->AddForce(toVec);

		Rotation(velo);

		LostCheck();
	}

	void TargetChase::LostCheck() {
		//視界に入っているかどうかを判断
		auto obj = GetGameObject();
		auto eyeRange = obj->GetComponent<EyeSearchRange>(false);
		if (eyeRange == nullptr) {
			return;
		}

		//視界外ならAstarを利用して追いかける。
		if (!eyeRange->IsLookTarget(m_target)) {
			auto probe = GetGameObject()->GetComponent<ProbeAstarMove>(false);
			if (probe) {
				probe->CalucRoute(m_target);
				m_updateFunc = &TargetChase::LostMove;

				//テスト実装
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
		//視界に入っているかどうかを判断
		auto obj = GetGameObject();
		auto eyeRange = obj->GetComponent<EyeSearchRange>(false);
		if (eyeRange == nullptr) {
			return;
		}

		if (eyeRange->IsLookTarget(m_target)) {  //一部のオブジェクトを障害物として扱わないようにする
			m_updateFunc = &TargetChase::LookMove;

			//テスト実装
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
		if (m_target == nullptr) {  //ターゲットが追従
			return;
		}

		if (m_updateFunc) {
			m_updateFunc(*this);
		}
	}

}

//endbasecross