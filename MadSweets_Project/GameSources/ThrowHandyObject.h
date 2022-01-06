
/*!
@file ThrowHandyObject.h
@brief ThrowHandyObjectクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "ThrowObject.h"

namespace basecross {

	class ThrowHandyObject : public ThrowObject	{

	public:

		ThrowHandyObject(const std::shared_ptr<Stage>& stage)
			:ThrowObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross