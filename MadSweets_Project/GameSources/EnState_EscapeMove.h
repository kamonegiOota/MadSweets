/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	/// <summary>
	/// �����Ă����Ԃ̃X�e�[�g
	/// </summary>
	class EnState_EscapeMove : public maru::StateMachine<BaseEnemy>
	{
		std::shared_ptr<GameObject> m_target;

	public:
		EnState_EscapeMove(const std::shared_ptr<BaseEnemy>& objPtr,
			const std::shared_ptr<GameObject>& target
		) :
			maru::StateMachine<BaseEnemy>(objPtr),
			m_target(target)
		{}

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

	};

}

//endbasecross