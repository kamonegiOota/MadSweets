
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "ThrowHandyObject.h"
#include "Velocity.h"
#include "ThrowObjectCtrl.h"

namespace basecross {

	void ThrowHandyObject::OnCreate() {
		//�����I�ɂ͌����ڂ̂ݏ���
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_SPHERE");

		auto col = AddComponent<CollisionSphere>();
		col->SetAfterCollision(AfterCollision::None);

		AddComponent<Velocity>();
		AddComponent<ThrowObjectCtrl>();
	}

}

//endbasecross