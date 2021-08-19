/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "TactileCtrl.h"
#include "MyUtility.h"

namespace basecross {

	void TactileCtrl::OnCreate() {

	}

	void TactileCtrl::OnCollisionExcute(std::shared_ptr<GameObject>& other) {
		if (other == GetGameObject()->GetParent()) {  //�����̐e�I�u�W�F�N�g��������Ȃ�
			return;
		}

		for (auto& action : m_excuteActions) {
			action(GetThis<TactileCtrl>(),other);
		}
	}
}

//endbasecross