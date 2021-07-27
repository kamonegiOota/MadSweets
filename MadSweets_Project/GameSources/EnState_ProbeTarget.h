/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
担当者：丸山 裕喜
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	//ターゲットの捜索ステート
	class EnState_ProbTarget : public maru::StateMachine<BaseEnemy>
	{
		std::shared_ptr<GameObject> m_target;

	public:

		EnState_ProbTarget(const std::shared_ptr<BaseEnemy>& owner,
			const std::shared_ptr<GameObject>& target
		) :
			maru::StateMachine<BaseEnemy>(owner),
			m_target(target)
		{}

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

	};

}

//endbasecorss