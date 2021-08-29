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

	struct AshiAnimationMember {
		Trigger escapeTrigger;
	};

	enum class AshiAnimationState {
		Walk,
		Escape,
	};

	class AshiAnimatorCtrl : public Component
	{
		using AshiAnimator = Animator<AshiAnimationMember, AshiAnimationState>;
		using AshiStateMachine = AnimatorMainStateMachine<AshiAnimationMember, AshiAnimationState>;

		ex_weak_ptr<PNTBoneModelDraw> m_draw;

		void CreateWalkAnimator(const std::shared_ptr<AshiStateMachine>& stateMachine);
		void CreateDashAnimator(const std::shared_ptr<AshiStateMachine>& stateMachine);

	public:
		AshiAnimatorCtrl(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<PNTBoneModelDraw>& draw)
			:Component(objPtr),m_draw(draw)
		{}

		void OnCreate() override{}
		void OnStart() override;

	};

}

//endbasecross