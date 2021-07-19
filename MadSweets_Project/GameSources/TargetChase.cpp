/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "TargetChase.h"
#include "MyUtility.h"

#include "EyeSearchRange.h"
#include "EnemyRotationCtrl.h"
#include "AstarCtrl.h"
#include "I_Chase.h"
#include "DebugObject.h"

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

		auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), m_target);

		auto pos = transform->GetPosition();
		pos += toVec.GetNormalized() * m_speed * delta;
		transform->SetPosition(pos);
		Rotation(toVec);

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
			auto astar = obj->GetComponent<AstarCtrl>();
			if (astar) {
				astar->SearchAstarForecastStart(m_target);
				//astar->SearchAstarStart(m_target);
				m_updateFunc = &TargetChase::LostMove;

				//テスト実装
				obj->GetComponent<PNTStaticDraw>()->SetDiffuse(Col4(1.0f, 0.0f, 1.0f, 1.0f));
			}
		}
	}


	void TargetChase::LostMove() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (!astar) {
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();

	 	auto selfPos = transform->GetPosition();
		auto targetPos = astar->GetCalucNodePos();

		if (astar->IsRouteEnd()) {  //ターゲットが最後の場所にたどり着いていたら、ステートを変更する
			ChangeStateMachine();  //ステートの変更
			return;
		}

		auto toVec = targetPos - selfPos;
		selfPos += toVec.GetNormalized() * m_speed * delta;
		transform->SetPosition(selfPos);
		Rotation(toVec);

		LookCheck();
	}

	void TargetChase::LookCheck() {
		//視界に入っているかどうかを判断
		auto obj = GetGameObject();
		auto eyeRange = obj->GetComponent<EyeSearchRange>(false);
		if (eyeRange == nullptr) {
			return;
		}

		if (eyeRange->IsLookTarget(m_target)) {
			m_updateFunc = &TargetChase::LookMove;

			//テスト実装
			obj->GetComponent<PNTStaticDraw>()->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
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
			chase->ChangeTargetLostState();
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