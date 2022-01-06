/*!
@file EnState_EscapeMove.h
@brief EnState_EscapeMove
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"
#include "EnemyStateNodeBase.h"

namespace basecross {

	/// <summary>
	/// �����Ă����Ԃ̃X�e�[�g
	/// </summary>
	class EnState_EscapeMove : public EnemyStateNodeBase<BaseEnemy>
	{
		ex_weak_ptr<GameObject> m_target;

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