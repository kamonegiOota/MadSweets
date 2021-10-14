/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
担当者：丸山 裕喜
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"
#include "EnemyStateNodeBase.h"

namespace basecross {

	/// <summary>
	/// 逃げている状態のステート
	/// </summary>
	class EnState_EscapeMove : public EnemyStateNodeBase<BaseEnemy>
	{
		std::shared_ptr<GameObject> m_target;

		void ChangeState();

	public:
		EnState_EscapeMove(const std::shared_ptr<BaseEnemy>& objPtr
		) :
			EnemyStateNodeBase<BaseEnemy>(objPtr)
		{}

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

	};

}

//endbasecross