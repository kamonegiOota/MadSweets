/*!
@file EnState_ProbTarget.h
@brief EnState_ProbTarget
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	//�^�[�Q�b�g�̑{���X�e�[�g
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