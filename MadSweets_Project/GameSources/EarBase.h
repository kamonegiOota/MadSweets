/*!
@file EarBase.h
@brief EarBase
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class EarBase : public Component
	{

	public:
		EarBase(const std::shared_ptr<GameObject>& objPtr) 
			:Component(objPtr)
		{}

	 	virtual void OnCreate() override {}
		virtual void OnUpdate() override {}

	};

}

//endbasecross