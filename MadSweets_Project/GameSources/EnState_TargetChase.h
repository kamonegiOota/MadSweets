/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
’S“–ÒFŠÛR —TŠì
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	class EnState_TargetChase : public EnemyStateNodeBase<BaseEnemy>
	{
	public:

		EnState_TargetChase(const std::shared_ptr<BaseEnemy>& owner
		) :
			EnemyStateNodeBase<BaseEnemy>(owner)
		{}
		
		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

	};

}

//endbasecross