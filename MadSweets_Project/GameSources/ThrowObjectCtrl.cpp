/*!
@file ThrowObjectCtrl.cpp
@brief ThrowObjectCtrl�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "ThrowObjectCtrl.h"
#include "Velocity.h"

#include "I_Damaged.h"
#include <DirectXMath.h>

#include "SoundHelper.h"

namespace basecross {

	void ThrowObjectCtrl::Rotation(const Vec3& direct) {
		auto newDirect = direct;
		auto rotMat = (Mat4x4)XMMatrixRotationAxis(newDirect.GetNormalized(), XM_PIDIV2);  //���������킹��
		rotMat *= (Mat4x4)XMMatrixRotationY(XM_PIDIV2);  //90�x�̂��ꂪ���邽�ߒ����B
		auto mat = transform->GetWorldMatrix();
		mat *= rotMat;

		transform->SetQuaternion(mat.quatInMatrix());
	}

	void ThrowObjectCtrl::Throw(const std::shared_ptr<GameObject>& owner, const Vec3& direct, const float& speed) {
		SetOwner(owner);

		auto velocity = GetGameObject()->GetComponent<Velocity>(false);
		if (!velocity) {
			velocity = GetGameObject()->AddComponent<Velocity>();
		}
		
		auto newDirect = direct;
		velocity->SetVelocity(newDirect.GetNormalized() * speed);

		Rotation(direct);  //�������Z�b�g���邽�߂̏���
	}

	void ThrowObjectCtrl::OnCollisionEnter(std::shared_ptr<GameObject>& other) {
		if (other == m_owner || other == m_owner->GetChild() || other == m_owner->GetParent()) {
			return;
		}

		//�����Ń_���[�W��^����
		auto damage = other->GetComponent<I_Damaged>(false);
		if (damage) {
			damage->Damage(m_attackPower);
		}

		SimpleSoundManager::OnePlaySE(L"CookieCrushSE", 30.0f);

		GetStage()->RemoveGameObject<GameObject>(GetGameObject());
	}

}

//endbasecorss