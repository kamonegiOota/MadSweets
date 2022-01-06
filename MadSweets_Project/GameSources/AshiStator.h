/*!
@file AshiStator.h
@brief AshiStator
�S���ҁF�ێR �T��
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include"Trigger.h"

#include "EnemyMainStateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	struct AshiStateTransitionMember {
		Trigger escapeTrigger;
		Trigger loseTrigger;
		Trigger plowlingTrigger;
	};

	enum class AshiStateType {
		Escape,
		Lose,
		Plowling,
	};

	class AshiStator : public Component
	{
		using TransitionMember = AshiStateTransitionMember;
		using StateType = AshiStateType;
		using StateMachine = EnemyMainStateMachine<BaseEnemy, StateType, TransitionMember>;

		std::shared_ptr<StateMachine> m_stateMachine;

		void CreateNodes();
		void CreateEdges();

	public :

		AshiStator(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {}
		void OnStart() override;
		void OnUpdate() override;


		//�A�N�Z�b�T---------------------------------------------------------------------

		TransitionMember& GetTransitionMember() {
			return m_stateMachine->GetTransitionStructMember();
		}

	};

}

//endbasecross