/*!
@file TitleNameObject.h
@brief TitleNameObject
’S“–ÒFŠÛR —TŠì
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class TitleNameObject : public UIObject
	{
		std::shared_ptr<UIObject> CreateUI(const wstring& texture);

	public:

		TitleNameObject(std::shared_ptr<Stage>& stage)
			:UIObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross