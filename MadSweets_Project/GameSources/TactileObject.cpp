/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
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

		//仮で存在するか見た目をつける
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");
	}

}

//endbasecross