
/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class ChubbyCompCtrl : public Component
	{

	public:
		
		ChubbyCompCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override {}

	};

}

//endbasecross