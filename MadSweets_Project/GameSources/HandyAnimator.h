/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
担当者：丸山 裕喜
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
		HideSearch,
	};

	class HandyAnimatorCtrl : public Component
	{
		using HandyAnimator = Animator<HandyAnimationMember, HandyAnimationState>;
		using HandyStateMachine = AnimatorMainStateMachine<HandyAnimationMember, HandyAnimationState>;

		ex_weak_ptr<PNTBoneModelDraw> m_draw;

		void CreateAnimator();
		void CreateToWalkAnimator(const std::shared_ptr<HandyStateMachine>& stateMachine);
		void CreateWalkAnimator(const std::shared_ptr<HandyStateMachine>& stateMachine);
		void CreateAttackAnimator(const std::shared_ptr<HandyStateMachine>& stateMachine);
		void CreateHideSearchAnimator(const std::shared_ptr<HandyStateMachine>& stateMachine);

	public:

		HandyAnimatorCtrl(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<PNTBoneModelDraw> draw
		)
			:Component(objPtr),
			m_draw(draw)
		{}

		void OnCreate() override {};
		void OnStart() override;
		void OnUpdate() override {};


		//アクセッサ------------------------------------------------------------------------------------
		std::shared_ptr<HandyAnimator> GetAnimator() const {
			return GetGameObject()->GetComponent<HandyAnimator>();
		}
	};

}

//endbasecross