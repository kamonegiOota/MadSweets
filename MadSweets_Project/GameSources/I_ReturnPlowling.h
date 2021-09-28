/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	class I_ReturnPlowling
	{

	public:

		virtual void StartReturnPlowling() = 0;
		virtual void EndReturnPlowling() = 0;
	};
}

//endbasecross