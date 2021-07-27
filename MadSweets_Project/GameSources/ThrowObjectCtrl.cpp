/*!
@file SearchObject.cpp
@brief SearchObjectなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "ThrowObjectCtrl.h"
#include "Velocity.h"

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

		//ここでダメージを与える
		GetStage()->RemoveGameObject<GameObject>(GetGameObject());
	}

}

//endbasecorss