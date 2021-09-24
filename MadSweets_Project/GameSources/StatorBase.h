/*!
@file StatorBase.h
@brief StatorBase
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class StatorBase : public Component
	{

	public:
		StatorBase(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{ }

	};

}

//endbasecross