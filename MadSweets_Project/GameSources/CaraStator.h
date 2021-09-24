/*!
@file StatorBase.h
@brief StatorBase
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class StatorBase;

	class CaraStator : public StatorBase
	{

	public:
		CaraStator(const std::shared_ptr<GameObject>& objPtr)
			:StatorBase(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};

}

//endbasecorss