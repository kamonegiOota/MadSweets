/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"
#include "EnemyRotationCtrl.h"

namespace basecross {

	void EnemyRotationCtrl::RotationProcess() {
		//«—ˆ“I‚É‚Í‚ä‚Á‚­‚è‰ñ“]‚·‚é‚æ‚¤‚É‚·‚éB
		transform->SetForward(m_direct);
	}

	void EnemyRotationCtrl::OnCreate() {
		m_direct = transform->GetForword();
	}

	void EnemyRotationCtrl::OnUpdate() {
		RotationProcess();
	}
}

//endbasecross