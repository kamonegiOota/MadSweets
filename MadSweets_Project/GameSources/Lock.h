/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "I_Damaged.h"

namespace basecross {

	class LockPlayer : public Component
	{

	public:
		LockPlayer(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override {}

		/// <summary>
		/// Plyaerの操作をActiveにするかどうか
		/// </summary>
		void SetPlayerOperationActive(bool isLock);

	};

}

//endbasecross