/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	class EnState_Attack : public maru::StateMachine<BaseEnemy>
	{
		std::shared_ptr<GameObject> m_target;

	public:
		
		EnState_Attack(const std::shared_ptr<BaseEnemy>& owner,
			const std::shared_ptr<GameObject>& target
		) :
			maru::StateMachine<BaseEnemy>(owner),
			m_target(target)
		{}

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

		
		//�A�N�Z�b�T------------------------------------------------------------------

		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}

	};

}

//endbasecross