/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
担当者：丸山 裕喜
*/

#pragma once

#include "BaseEnemy.h"

namespace basecross {

	class I_Probe {

	public:

		virtual void StartProbe() = 0;
		virtual void EndProbe() = 0;

		/// <summary>
		/// 隠れるオブジェクトの中を覗く処理
		/// </summary>
		virtual void HideSearchAnimationStart() = 0;
	};

	

}

//endbasecross