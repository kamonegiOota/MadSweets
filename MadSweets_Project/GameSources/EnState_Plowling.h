/*!
@file EnState_Plowling.h
@brief EnState_Plowling
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	/// <summary>
	/// �G�l�~�[���p�j����Ƃ��̃X�e�[�g
	/// </summary>
	class EnState_Plowling : public maru::StateMachine<BaseEnemy>
	{

	public:
		EnState_Plowling(const std::shared_ptr<BaseEnemy>& objPtr)
			:maru::StateMachine<BaseEnemy>(objPtr)
		{}

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;
	};

}

//endbasecross