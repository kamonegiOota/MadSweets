/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "ObjectTransport.h"

#include "DebugObject.h"

namespace basecross {

	void ObjectTransport::ParentSet() {
		auto target = m_target.lock();
		if (target == nullptr) {
			return;
		}

		target->SetParent(GetGameObject());
	}

	void ObjectTransport::Move() {
		auto target = m_target.lock();
		if (target) {
			auto targetPosition = target->GetComponent<Transform>()->GetPosition();
			auto setPosition = targetPosition + m_offset;
			GetGameObject()->GetComponent<Transform>()->SetPosition(setPosition);
		}
	}

	void ObjectTransport::OnCreate() {
		ParentSet();
	}

	void ObjectTransport::OnUpdate() {
		//Move();

		//auto target = m_target.lock();
		//if (IsTargetEmpty()) {
		//	DebugObject::AddString(L"targetNull");
		//}
	}

}

//endbasecross