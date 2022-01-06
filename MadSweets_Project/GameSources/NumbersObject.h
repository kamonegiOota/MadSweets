
/*!
@file NumbersObject.h
@brief NumbersObjectクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//複数の数字を扱うオブジェクト
	class NumbersObject : public GameObject
	{

	public:
		NumbersObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross