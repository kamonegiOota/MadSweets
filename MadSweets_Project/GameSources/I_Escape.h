/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
担当者：丸山 裕喜
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	/// <summary>
	/// 逃げる処理を記述するInterface
	/// </summary>
	class I_Escape {

	public:
		
		virtual void ChangeEscapeState(const std::shared_ptr<GameObject>& target) = 0;
		virtual void SuccessEscape() = 0;  //逃げ切り成功
	};

}

//endbasecross