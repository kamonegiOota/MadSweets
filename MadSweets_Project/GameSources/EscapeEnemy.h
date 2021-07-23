/*!
@file BaseEnemy.h
@brief BaseEnemy
担当者：丸山 裕喜
*/

#pragma once

#include "BaseEnemy.h"
#include "StateMachine.h"
#include "I_Escape.h"

namespace basecross {

	/// <summary>
	/// プレイヤ―を見つけたら逃げる動作をするEnemy
	/// </summary>
	class EscapeEnemy : public BaseEnemy, public I_Escape
	{

	public:

		EscapeEnemy(const std::shared_ptr<GameObject>& objPtr)
			:BaseEnemy(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		//インターフェースの実装
		void ChangeEscapeState(const std::shared_ptr<GameObject>& target) override;
		void SuccessEscape() override;

		//void EyeSearch();  //目のサーチ
	};

}

//endbasecross