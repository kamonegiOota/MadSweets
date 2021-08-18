/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "WallEvasionTactile.h"
#include "MyUtility.h"

#include "WallEvasion.h"

namespace basecross {

	void WallEvasionTactile::OnCreate() {

	}

	void WallEvasionTactile::OnCollisionExcute(std::shared_ptr<GameObject>& other) {
		if (other == GetGameObject()->GetParent()) {  //自分の親オブジェクトだったら省く
			return;
		}

		for (auto& action : m_excuteActions) {
			action(GetThis<WallEvasionTactile>(),other);
		}
	}
}

//endbasecross