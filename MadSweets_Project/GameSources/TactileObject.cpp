/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇÀ‘Ì
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

		//‰¼‚Å‘¶İ‚·‚é‚©Œ©‚½–Ú‚ğ‚Â‚¯‚é
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");
	}

}

//endbasecross