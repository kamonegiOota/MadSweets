/*!
@file EnState_ProbTarget.h
@brief EnState_ProbTarget
担当者：丸山 裕喜
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	//ターゲットの捜索ステート
	class EnState_ProbTarget : public EnemyStateNodeBase<BaseEnemy>
	{
	public:

		EnState_ProbTarget(const std::shared_ptr<BaseEnemy>& owner
		) :
			EnemyStateNodeBase<BaseEnemy>(owner)
		{}

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

	};

}

//endbasecorss