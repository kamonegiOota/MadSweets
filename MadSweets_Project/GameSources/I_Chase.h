/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
担当者：丸山 裕喜
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	class I_Chase
	{
	public:
		virtual void ChangeChaseState(const std::shared_ptr<GameObject>& target) = 0;
		virtual void ChangeTargetLostState() = 0;  //ターゲットを見失ったときの処理
	};
}

//endbasecross