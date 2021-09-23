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


		//アクセッサ------------------------------------------------------------------------------

		std::shared_ptr<HandyStateMachine> GetStateMachine() const {
			return GetGameObject()->GetComponent<HandyStateMachine>();
		}
	};

}

//endbasecross