/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "EscapeEnemyStator.h"

namespace basecross {

	void EscapeEnemyStator::OnCreate() {
		m_stateMachine = make_shared<StateMachine>();
	}

}

//endbasecross