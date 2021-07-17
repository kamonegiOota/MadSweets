/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
’S“–ÒFŠÛR —TŠì
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	class EnState_TargetChase : public maru::StateMachine<BaseEnemy>
	{
		std::shared_ptr<GameObject> m_target;

	public:

		EnState_TargetChase(const std::shared_ptr<BaseEnemy>& owner,
			const std::shared_ptr<GameObject>& target
		) :
			maru::StateMachine<BaseEnemy>(owner),
			m_target(target)
		{}
		
		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

	};

}

//endbasecross