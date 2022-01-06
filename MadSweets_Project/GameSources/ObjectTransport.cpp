/*!
@file ObjectTransport.cpp
@brief ObjectTransport‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "ObjectTransport.h"

#include "DebugObject.h"

namespace basecross {

	void ObjectTransport::Move() {
		auto target = m_target.lock();
		if (target) {
			auto setPosition = transform->GetPosition() + m_offset;
			target->GetComponent<Transform>()->SetPosition(setPosition);
		}
	}

	void ObjectTransport::Rotation() {
		//auto parent = GetGameObject()->GetParent();
		//if (parent) {
		//	auto parentTrans = parent->GetComponent<Transform>();
		//	auto beforeQuat = parentTrans->GetBeforeQuaternion();
		//	auto nowQuat = parentTrans->GetQuaternion();
		//	auto diffQuat = nowQuat * XMQuaternionInverse(beforeQuat);

		//	auto selfQuat = transform->GetQuaternion();
		//	auto setQuat = selfQuat * (Quat)XMQuaternionInverse(diffQuat);
		//	
		//	transform->SetQuaternion(setQuat);
		//}
	}

	void ObjectTransport::ScaleAdjust(const std::shared_ptr<GameObject>& target) {
		if (target == nullptr) {
			return;
		}

		auto trans = target->GetComponent<Transform>();
		auto scale = trans->GetScale();
		scale *= m_targetScaleAdjust;

		trans->SetScale(scale);
	}

	void ObjectTransport::OnCreate() {

	}

	void ObjectTransport::OnUpdate() {
		Move();
	}
}

//endbasecross