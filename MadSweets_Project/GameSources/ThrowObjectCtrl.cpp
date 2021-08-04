/*!
@file SearchObject.cpp
@brief SearchObject�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "ThrowObjectCtrl.h"
#include "Velocity.h"

#include "I_Damaged.h"

namespace basecross {

	void ThrowObjectCtrl::Throw(const std::shared_ptr<GameObject>& owner, const Vec3& direct, const float& speed) {
		SetOwner(owner);

		auto velocity = GetGameObject()->GetComponent<Velocity>(false);
		if (!velocity) {
			velocity = GetGameObject()->AddComponent<Velocity>();
		}
		
		auto newDirect = direct;
		velocity->SetVelocity(newDirect.GetNormalized() * speed);
	}

	void ThrowObjectCtrl::OnCollisionEnter(std::shared_ptr<GameObject>& other) {
		if (other == m_owner) {
			return;
		}

		//�����Ń_���[�W��^����
		auto damage = other->GetComponent<I_Damaged>(false);
		if (damage) {
			//damage->Damage(m_attackPower);
		}

		GetStage()->RemoveGameObject<GameObject>(GetGameObject());
	}

}

//endbasecorss