/*!
@file GraphNode.cpp
@brief GraphNodeÇ»Ç«é¿ëÃ
*/

#include "stdafx.h"
#include "Project.h"

#include "TargetChase.h"
#include "MyUtility.h"

#include "EyeSearchRange.h"
#include "AstarCtrl.h"
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

		LostCheck();
	}

	void TargetChase::LostCheck() {
		//éãäEÇ…ì¸Ç¡ÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©Çîªíf
		auto obj = GetGameObject();
		auto eyeRange = obj->GetComponent<EyeSearchRange>(false);
		if (eyeRange == nullptr) {
			return;
		}

		//éãäEäOÇ»ÇÁAstarÇóòópÇµÇƒí«Ç¢Ç©ÇØÇÈÅB
		if (!eyeRange->IsLookTarget(m_target)) {
			auto astar = obj->GetComponent<AstarCtrl>();
			if (astar) {
				astar->SearchAstarForecastStart(m_target);
				m_updateFunc = &TargetChase::LostMove;
			}
		}
	}


	void TargetChase::LostMove() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (!astar) {
			return;
		}
		
		if (astar->IsRouteEnd()) {
			LookCheck();
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();

	 	auto selfPos = transform->GetPosition();
		auto targetPos = astar->GetCalucNodePos();

		auto toVec = targetPos - selfPos;
		selfPos += toVec.GetNormalized() * m_speed * delta;
		transform->SetPosition(selfPos);

		LookCheck();
	}

	void TargetChase::LookCheck() {
		//éãäEÇ…ì¸Ç¡ÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©Çîªíf
		auto obj = GetGameObject();
		auto eyeRange = obj->GetComponent<EyeSearchRange>(false);
		if (eyeRange == nullptr) {
			return;
		}

		if (eyeRange->IsLookTarget(m_target)) {
			m_updateFunc = &TargetChase::LookMove;
		}
	}

	void TargetChase::OnCreate() {
		m_updateFunc = &TargetChase::LookMove;
	}

	void TargetChase::OnUpdate() {
		if (m_target == nullptr) {  //É^Å[ÉQÉbÉgÇ™í«è]
			return;
		}

		if (m_updateFunc) {
			m_updateFunc(*this);
		}

		//LookMove();
	}

}

//endbasecross