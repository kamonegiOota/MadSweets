/*!
@file CaraStator.h
@brief CaraStator
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "ChaseEnemyStator.h"

namespace basecross {

	class StatorBase;
	class itbs::Utility::Trigger;
	class BaseEnemy;
	template<class node_type, class EnumType, class TransitionMember>
	class EnemyMainStateMachine;

	struct CaraStateTransitionMember
	{
		Trigger chaseTrigger;
		Trigger attackTrigger;
		Trigger probeTrigger;
		Trigger loseTrigger;
		Trigger plowlingTrigger;
		Trigger soundCheckTrigger;
	};

	enum class CaraStateType
	{
		Plowling,
		Attack,
		Chase,
		Probe,
		Lose,
		SoundCheck,
	};

	class CaraStator : public StatorBase
	{
		using CaraStateMachine = EnemyMainStateMachine<BaseEnemy, CaraStateType, CaraStateTransitionMember>;

		std::shared_ptr<CaraStateMachine> m_stateMachine;

		void CreateNodes();
		void CreateEdges();

	public:
		CaraStator(const std::shared_ptr<GameObject>& objPtr)
			:StatorBase(objPtr)
		{}

		void OnCreate() override {}
		void OnStart() override;
		void OnUpdate() override;


		//アクセッサ-------------------------------------------------------

		CaraStateTransitionMember& GetTransitionMember() {
			return m_stateMachine->GetTransitionStructMember();
		}
	};

}

//endbasecorss