/*!
@file MaruStage.h
@brief MaruStage
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class WeightGaugeUI : public UIObject
	{
		std::shared_ptr<UIObject> CreateUI(const wstring& texture);

	public:

		WeightGaugeUI(std::shared_ptr<Stage>& stage)
			:UIObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross