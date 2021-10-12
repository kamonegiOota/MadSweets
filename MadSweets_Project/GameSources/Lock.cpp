/*!
@file PositionDrawComp.h
@brief PositionDrawComp
’S“–ŽÒFŠÛŽR —TŠì
*/

#include "stdafx.h"
#include "Project.h"

#include "Lock.h"

#include "PlayerMover.h"
#include "DebugObject.h"

namespace basecross {

	void LockPlayer::SetPlayerOperationActive(bool isActive) {
		auto obj = GetGameObject();
		DebugObject::AddString(L"SetPlayerOperationActive");
		auto mover = obj->GetComponent<PlayerMover>();
		if (mover) {
			mover->SetUpdateActive(isActive);
		}
	}

}

//endbasecross