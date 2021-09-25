/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
担当者：丸山 裕喜
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include"Trigger.h"

#include "EnemyMainStateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	struct EscapeEnemyStateTransitionMember {
		Trigger escapeTrigger;
		Trigger loseTrigger;
		Trigger plowlingTrigger;
	};

	enum class EscapeEnemyStateType {
		Escape,
		Lose,
		Plowling,
	};

	class EscapeEnemyStator : public Component
	{
		using TransitionMember = EscapeEnemyStateTransitionMember;
		using StateType = EscapeEnemyStateType;
		using StateMachine = EnemyMainStateMachine<BaseEnemy, StateType, TransitionMember>;

		std::shared_ptr<StateMachine> m_stateMachine;

	public :

		EscapeEnemyStator(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate();
		void OnStart() {}
		void OnUpdate() {}


		//アクセッサ---------------------------------------------------------------------

		TransitionMember& GetTransitionMemeber() {
			return m_stateMachine->GetTransitionStructMember();
		}

	};

}

//endbasecross