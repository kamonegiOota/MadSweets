/*!
@file BaseEnemy.cpp
@brief BaseEnemy�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "EscapeEnemy.h"

#include "EnState_Plowling.h"

namespace basecross {

	void EscapeEnemy::OnCreate() {
		ChangeStateMachine<EnState_Plowling>();
	}

	void EscapeEnemy::OnUpdate() {
		BaseEnemy::OnUpdate();
	}

}