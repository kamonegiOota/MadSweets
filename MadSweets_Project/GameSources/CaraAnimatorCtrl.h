/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
�S���ҁF�ێR �T��
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "AnimationHelper.h"
#include"Trigger.h"

namespace basecross {

	struct CaraAnimationMember {
		Trigger attackTrigger;
		Trigger hideSearchTrigger;
	};

	enum class CaraAnimationState {
		Walk,
		Attack,
		HideSearch,
	};

	class CaraAnimatorCtrl : public Component
	{
		using CaraAnimator = Animator<CaraAnimationMember, CaraAnimationState>;
		using CaraStateMachine = AnimatorMainStateMachine<CaraAnimationMember, CaraAnimationState>;

		ex_weak_ptr<PNTBoneModelDraw> m_draw;

		void CreateWalkAnimator(const std::shared_ptr<CaraStateMachine>& stateMachine);
		void CreateAttackAnimator(const std::shared_ptr<CaraStateMachine>& stateMachine);
		void CreateHideSearchAnimator(const std::shared_ptr<CaraStateMachine>& stateMachine);

	public:
		CaraAnimatorCtrl(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<PNTBoneModelDraw>& draw
		):
			Component(objPtr),
			m_draw(draw)
		{}

		void OnCreate() override {}
		void OnStart() override;
		void OnUpdate() override {}


		//�A�N�Z�b�T------------------------------------------------------------------------------------------
		std::shared_ptr<CaraAnimator> GetAnimator() const {
			return GetGameObject()->GetComponent<CaraAnimator>();
		}

	};

}