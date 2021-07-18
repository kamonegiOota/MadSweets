/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
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
		//���E�ɓ����Ă��邩�ǂ����𔻒f
		auto obj = GetGameObject();
		auto eyeRange = obj->GetComponent<EyeSearchRange>(false);
		if (eyeRange == nullptr) {
			return;
		}

		//���E�O�Ȃ�Astar�𗘗p���Ēǂ�������B
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
		//���E�ɓ����Ă��邩�ǂ����𔻒f
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
		if (m_target == nullptr) {  //�^�[�Q�b�g���Ǐ]
			return;
		}

		if (m_updateFunc) {
			m_updateFunc(*this);
		}

		//LookMove();
	}

}

//endbasecross