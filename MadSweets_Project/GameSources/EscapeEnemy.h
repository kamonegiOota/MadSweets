/*!
@file BaseEnemy.h
@brief BaseEnemy
担当者：丸山 裕喜
*/

#pragma once

#include "BaseEnemy.h"
#include "StateMachine.h"

namespace basecross {

	/// <summary>
	/// プレイヤ―を見つけたら逃げる動作をするEnemy
	/// </summary>
	class EscapeEnemy : public BaseEnemy
	{

	public:

		EscapeEnemy(const std::shared_ptr<GameObject>& objPtr)
			:BaseEnemy(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};

}

//endbasecross