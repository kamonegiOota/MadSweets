/*!
@file TactileObject.cpp
@brief TactileObject�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "TactileObject.h"
#include "TactileCtrl.h"

namespace basecross {

	void TactileObject::OnCreate() {
		AddComponent<TactileCtrl>();

		auto col = AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);

		//���ő��݂��邩�����ڂ�����
		//auto draw = AddComponent<PNTStaticDraw>();
		//draw->SetMeshResource(L"DEFAULT_CUBE");

		transform->SetScale(0.1f, 0.1f, 1.0f);
	}

}

//endbasecross