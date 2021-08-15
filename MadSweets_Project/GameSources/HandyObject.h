/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
íSìñé“ÅFä€éR óTäÏ
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "AnimationHelper.h"
#include"Trigger.h"

namespace basecross {

	struct HandyAnimationMember {
		Trigger attackTrigger;
		Trigger hideSearchTrigger;
	};

	enum class HandyAnimationState {
		Walk,
		Attack,
		hideSearch,
	};

	class HandyObject : public GameObject
	{
		void CreatePlowlingRoute();
		void CreateAnimetor();
		void CreateWalkAnime(const std::shared_ptr<AnimatorMainStateMachine<HandyAnimationMember, HandyAnimationState>>& stateMachine);
		void CreateAttackAnime(const std::shared_ptr<AnimatorMainStateMachine<HandyAnimationMember, HandyAnimationState>>& stateMachine);

	public:
		HandyObject(std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

		//âºé¿ëï
		void OnUpdate() override;
	};

}

//endbasecross