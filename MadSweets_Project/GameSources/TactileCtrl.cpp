/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "TactileCtrl.h"
#include "MyUtility.h"

namespace basecross {

	void TactileCtrl::OnCreate() {

	}

	void TactileCtrl::OnCollisionExcute(std::shared_ptr<GameObject>& other) {
		if (other == GetGameObject()->GetParent()) {  //自分の親オブジェクトだったら省く
			return;
		}

		for (auto& action : m_excuteActions) {
			action(GetThis<TactileCtrl>(),other);
		}
	}
}

//endbasecross