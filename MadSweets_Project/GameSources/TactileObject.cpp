/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "TactileObject.h"
#include "WallEvasionTactile.h"

namespace basecross {

	void TactileObject::OnCreate() {
		AddComponent<WallEvasionTactile>();

		auto col = AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);

		//���ő��݂��邩�����ڂ�����
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");
	}

}

//endbasecross