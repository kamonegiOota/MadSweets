/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "Mathf.h"
#include "DebugObject.h"

namespace basecross {

	class FlameMatch : public Component
	{

	public:

		FlameMatch(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override;

		/// <summary>
		/// ゲームスタート
		/// </summary>
		void StartGame();
	};

}

//endbasecross