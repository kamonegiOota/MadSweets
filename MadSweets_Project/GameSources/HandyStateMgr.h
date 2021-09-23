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
		TargetChase,
		TargetProbe,
		TargetLose,
	};

	class HandyStateMgr : public Component
	{
	public:
		using HandyStateMachine = EnemyMainStateMachine<maru::StateMachine<BaseEnemy>, HandyStateType, HandyStateTransitionMember>;

	private:

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
			return GetGameObject()->GetComponent<HandyStateMachine>();
		}
	};

}

//endbasecross