/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
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
		if (other == GetGameObject()->GetParent()) {  //�����̐e�I�u�W�F�N�g��������Ȃ�
			return;
		}

		for (auto& action : m_excuteActions) {
			action(GetThis<WallEvasionTactile>(),other);
		}
	}
}

//endbasecross