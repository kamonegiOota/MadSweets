/*!
@file EnState_Attack.h
@brief EnState_Attack
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"
#include "EnemyStateNodeBase.h"

namespace basecross {

	class EnState_Attack : public EnemyStateNodeBase<BaseEnemy>
	{
	public:
		
		EnState_Attack(const std::shared_ptr<BaseEnemy>& owner
		) :
			EnemyStateNodeBase<BaseEnemy>(owner)
		{}

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

		
		//�A�N�Z�b�T------------------------------------------------------------------

	};

}

//endbasecross