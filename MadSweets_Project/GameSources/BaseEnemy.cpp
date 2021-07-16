/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "BaseEnemy.h"

#include "EnState_TargetChase.h"
#include "EnState_Plowling.h"
#include "DebugObject.h"

namespace basecross {

	BaseEnemy::BaseEnemy(const std::shared_ptr<GameObject>& objPtr)
		:Component(objPtr)
	{}

	void BaseEnemy::OnCreate() {
		//ChangeStateMachine(make_shared<EnState_Plowling>(GetThis<BaseEnemy>()));
	}

	void BaseEnemy::OnUpdate() {
		if (m_stateMachine) {
			m_stateMachine->OnUpdate();
		}

		//�e�X�g����
		//auto key = App::GetApp()->GetMyInputDevice()->GetKeyBoard();
		//if(key.IsInputDown(itbs::Input::KeyCode::A)) {
		//	
		//}
	}

	void BaseEnemy::ChangeStateMachine(const std::shared_ptr<maru::StateMachine<BaseEnemy>>& newState) {
		if (m_stateMachine) {
			m_stateMachine->OnExit();
		}

		newState->OnStart();
		m_stateMachine = newState;
	}

}

//endbasecross