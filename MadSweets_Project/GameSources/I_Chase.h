/*!
@file I_Chase.h
@brief I_Chase
担当者：丸山 裕喜
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	class I_Chase
	{
	public:
		virtual void ChangeChaseState(const std::shared_ptr<GameObject>& target) = 0;  //追いかける処理に変更する時
		virtual void ChangeTargetLostState(const std::shared_ptr<GameObject>& target) = 0;  //ターゲットを見失ったときの処理
	};
}

//endbasecross