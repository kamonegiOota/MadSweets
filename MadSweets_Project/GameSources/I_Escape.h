/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	/// <summary>
	/// �����鏈�����L�q����Interface
	/// </summary>
	class I_Escape {

	public:
		
		virtual void ChangeEscapeState(const std::shared_ptr<GameObject>& target) = 0;
		virtual void SuccessEscape() = 0;  //�����؂萬��
	};

}

//endbasecross