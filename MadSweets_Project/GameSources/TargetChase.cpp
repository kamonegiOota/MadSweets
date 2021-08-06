/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
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

#include "ProbeAstarMove.h"
#include "HiddenComponent.h"

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
	
	bool TargetChase::TargetEyeRangeHide() {
		auto obj = GetGameObject();
		auto eyeRange = obj->GetComponent<EyeSearchRange>(false);

		//視界の先に隠れるオブジェクトが合ってそこにplayerが隠れていたらそれをターゲットにする。
		auto hides = maru::MyUtility::GetComponents<HiddenComponent>();
		for (auto& hide : hides) {
			if (eyeRange->IsInEyeRange(hide->GetGameObject())) {  //本来はEyeRangeで判断
				auto toVec = maru::MyUtility::CalucToTargetVec(m_target, hide->GetGameObject());
				if (toVec.length() <= 0.01f) {  //限りなく近いということは隠れたという事。
					ChangeStateMachine();  //ステートの変更
					//ターゲットを今目の前に隠れたオブジェクトにする。
					GetGameObject()->GetComponent<TargetProbe>()->StartProb(hide->GetGameObject());
					return true;
				}
			}
		}

		return false;
	}

	void TargetChase::LostTarget() {
		if (m_chaseMode == ChaseMode::Lost) {  //ロスト状態なら処理をしない。
			return;
		}

		//見失った時の処理。
		auto obj = GetGameObject();
		auto eyeRange = obj->GetComponent<EyeSearchRange>(false);

		//視界の先に隠れるオブジェクトが合ってそこにplayerが隠れていたらそれをターゲットにする。
		auto isTargetHide = TargetEyeRangeHide();
		if (isTargetHide) {  //隠れたらその後の処理をしない。
			return;
		}

		auto probe = GetGameObject()->GetComponent<ProbeAstarMove>(false);
		if (probe) {
			//通常探索
			probe->CalucRoute(m_target);
			m_updateFunc = &TargetChase::LostMove;

			//テスト実装
			auto draw = obj->GetComponent<BcBaseDraw>(false);
			if (draw) {
				draw->SetDiffuse(Col4(1.0f, 0.0f, 1.0f, 1.0f));
			}
		}

		m_chaseMode = ChaseMode::Lost;
	}

	void TargetChase::FindTarget() {
		m_updateFunc = &TargetChase::LookMove;

		//テスト実装
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

		auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), m_target);
		
		auto maxSpeed = 4.0f;  //将来的にメンバ変数化
		auto velo = velocity->GetVelocity();
		auto force = UtilVelocity::CalucSeekVec(velo, toVec, maxSpeed);

		velocity->AddForce(toVec);

		Rotation(velo);

		LookCheck();
		//LostCheck();
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

		//視界外にいるかどうか？
		if (eyeRange->IsLookTarget(m_target)) {
			FindTarget();
		}
		else{
			//見失ったならAstarを利用して追いかける。
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