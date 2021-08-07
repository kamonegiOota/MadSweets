/*!
@file PositionDrawComp.h
@brief PositionDrawComp
�S���ҁF�ێR �T��
*/

#include "stdafx.h"
#include "Project.h"
#include "PlayerStatusMgr.h"

#include "DebugObject.h"

namespace basecross {

	void PlayerStatusMgr::Damage(const float& damage) {
		m_param.hp += -damage;

		if (m_param.hp <= 0.0f) {
			m_param.hp = 0.0f;
			ChangeState(PlayerStaus::Dest);
		}
	}

	void PlayerStatusMgr::OnUpdate() {
		//DebugObject::AddFloat(m_param.hp);
	}

}

//endbasecross