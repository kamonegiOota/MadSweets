/*!
@file StatorBase.h
@brief StatorBase
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "StatorBase.h"
#include "BaseEnemy.h"
#include "Trigger.h"
#include "EnemyMainStateMachine.h"

namespace basecross {

	//class StatorBase;
	//class itbs::Utility::Trigger;
	//class BaseEnemy;
	//template<class node_type, class EnumType, class TransitionMember>
	//class EnemyMainStateMachine;

	//struct ChaseStateTransitionMember
	//{
	//	Trigger chaseTrigger;
	//	Trigger attackTrigger;
	//	Trigger probeTrigger;
	//	Trigger loseTrigger;
	//	Trigger plowlingTrigger;
	//};

	//enum class ChaseStateType
	//{
	//	Plowling,
	//	Attack,
	//	Chase,
	//	Probe,
	//	Lose,
	//};

	//class ChaseEnemyStator : public StatorBase
	//{
	//	using ChaseStateMachine = EnemyMainStateMachine<BaseEnemy, ChaseStateType, ChaseStateTransitionMember>;

	//	std::shared_ptr<ChaseStateMachine> m_stateMachine;

	//	void CreateNodes();
	//	void CreateEdges();

	//public:
	//	ChaseEnemyStator(const std::shared_ptr<GameObject>& objPtr)
	//		:StatorBase(objPtr)
	//	{}

	//	void OnCreate() override {}
	//	void OnStart() override;
	//	void OnUpdate() override;


	//	//アクセッサ-------------------------------------------------------

	//	ChaseStateTransitionMember& GetTransitionMember() {
	//		return m_stateMachine->GetTransitionStructMember();
	//	}
	//};

}

//endbasecorss