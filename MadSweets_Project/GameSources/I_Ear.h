/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	class I_Ear 
	{

	public:

		virtual void Listen() = 0;
		virtual void EndListen() = 0;
	};

}

//endbasecross