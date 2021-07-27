/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
SÒFÛR Tì
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	/// <summary>
	/// ¦°éðLq·éInterface
	/// </summary>
	class I_Escape {

	public:
		
		virtual void ChangeEscapeState(const std::shared_ptr<GameObject>& target) = 0;
		virtual void SuccessEscape() = 0;  //¦°Øè¬÷
	};

}

//endbasecross