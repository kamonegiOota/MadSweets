/*!
@file EnState_TargetChase.h
@brief EnState_TargetChase
担当者：丸山 裕喜
*/

#pragma once

namespace basecross {

	/// <summary>
	/// 逃げる処理を記述するInterface
	/// </summary>
	class I_Escape {

	public:
		
		virtual void StartEscape() = 0;
		virtual void SuccessEscape() = 0;  //逃げ切り成功
	};

}

//endbasecross