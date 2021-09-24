/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
�S���ҁF�ێR �T��
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include"Trigger.h"

#include "EnemyMainStateMachine.h"
#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	struct HandyStateTransitionMember {
		Trigger chaseTrigger;
		Trigger attackTrigger;
		Trigger probeTrigger;
		Trigger loseTrigger;
		Trigger plowlingTrigger;
	};

	enum class HandyStateType {
		Plowling,
		Attack,
		Chase,
		Probe,
		Lose,
	};

	class HandyStateMgr : public Component
	{
	public:
		using HandyStateMachine = EnemyMainStateMachine<BaseEnemy, HandyStateType, HandyStateTransitionMember>;

	private:
		std::shared_ptr<HandyStateMachine> m_stateMachine;

		void AddNodes(const std::shared_ptr<HandyStateMachine>& state);
		void AddEdges(const std::shared_ptr<HandyStateMachine>& state);

	public:

		HandyStateMgr(std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() {}
		void OnStart();
		void OnUpdate();


		//�A�N�Z�b�T------------------------------------------------------------------------------

		std::shared_ptr<HandyStateMachine> GetStateMachine() const {
			return m_stateMachine;
		}
	};

}

//endbasecross