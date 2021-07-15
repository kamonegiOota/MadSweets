
/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class MTestBox : public GameObject
	{

	public:
		MTestBox(const std::shared_ptr<Stage>& stage):
			GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross