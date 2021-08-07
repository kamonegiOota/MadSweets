/*!
@file GameManager.cpp
@brief GameManagerクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "PulledSweets.h"
#include "EatenComponent.h"
#include "MyUtility.h"

#include "DebugObject.h"

namespace basecross {

	Vec3 PulledSweets::CalucPulledVec() {
		auto reVec = Vec3(0.0f);

		auto eatens = maru::MyUtility::GetComponents<EatenComponent>();
		for (auto& eaten : eatens) {
			auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), eaten->GetGameObject());
			if (toVec.length() < m_range) {
				reVec += toVec;
			}
		}

		return reVec;
	}

	void PulledSweets::PulledMove() {
		auto delta = App::GetApp()->GetElapsedTime();

		auto moveVec = CalucPulledVec();

		auto pos = transform->GetPosition();
		pos += moveVec.normalize() * m_speed * delta;
		transform->SetPosition(pos);
	}


	void PulledSweets::OnCreate() {
		//SetUpdateActive(false);
	}

	void PulledSweets::OnStart() {
		//m_eatenComps = maru::MyUtility::GetComponents<EatenComponent>();
		//DebugObject::sm_wss << L"eatenSize:";
		//DebugObject::AddFloat((float)m_eatenComps.size(), true);
	}

	void PulledSweets::OnUpdate() {
		PulledMove();
	}

}

//endbasecross