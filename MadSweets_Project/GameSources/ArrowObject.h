
/*!
@file ArrowObject.h
@brief ArrowObjectクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class ArrowObject : public GameObject
	{

	public:

		ArrowObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross