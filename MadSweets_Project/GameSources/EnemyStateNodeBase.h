
/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "NodeBase.h"

namespace basecross {

	template<class EnemyType>
	class EnemyStateNodeBase : public NodeBase<EnemyType>
	{

	public:

		EnemyStateNodeBase(const std::shared_ptr<EnemyType>& owner)
			:NodeBase<EnemyType>(owner)
		{}

	};

}

//endbasecross