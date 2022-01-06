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

#include "StatorBase.h"

namespace basecross {

	struct HandyStateTransitionMember {
		Trigger chaseTrigger;
		Trigger attackTrigger;
		Trigger probeTrigger;
		Trigger loseTrigger;
		Trigger plowlingTrigger;
		Trigger soundCheckTrigger;
	};

	enum class HandyStateType {
		Plowling,
		Attack,
		Chase,
		Probe,
		Lose,
		SoundCheck,
	};

	class HandyStator : public StatorBase
	{
	public:
		using HandyStateMachine = EnemyMainStateMachine<BaseEnemy, HandyStateType, HandyStateTransitionMember>;

	private:
		std::shared_ptr<HandyStateMachine> m_stateMachine;

		void AddNodes(const std::shared_ptr<HandyStateMachine>& state);
		void AddEdges(const std::shared_ptr<HandyStateMachine>& state);

	public:

		HandyStator(std::shared_ptr<GameObject>& objPtr)
			:StatorBase(objPtr)
		{}

		void OnCreate() {}
		void OnStart();
		void OnUpdate();


		//アクセッサ------------------------------------------------------------------------------

		std::shared_ptr<HandyStateMachine> GetStateMachine() const {
			return m_stateMachine;
		}

		HandyStateTransitionMember& GetTransitionMember() const {
			return m_stateMachine->GetTransitionStructMember();
		}

		HandyStateType GetStateType() const {
			return m_stateMachine->GetNowType();
		}
	};

}

//endbasecross