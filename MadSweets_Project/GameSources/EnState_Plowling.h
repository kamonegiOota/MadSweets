/*!
@file EnState_Plowling.h
@brief EnState_Plowling
担当者：丸山 裕喜
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	/// <summary>
	/// エネミーが徘徊するときのステート
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