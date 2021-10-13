/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "AshiStator.h"

namespace basecross {

	void AshiStator::OnCreate() {
		m_stateMachine = make_shared<StateMachine>();
	}

}

//endbasecross