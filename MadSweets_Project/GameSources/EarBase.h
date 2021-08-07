/*!
@file EarBase.h
@brief EarBase
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "MyUtility.h"

namespace basecross {

	class EarBase : public Component
	{

	public:
		EarBase(const std::shared_ptr<GameObject>& objPtr) 
			:Component(objPtr)
		{}

	 	virtual void OnCreate() override {}
		virtual void OnUpdate() override {}

		virtual void Listen(const std::shared_ptr<GameObject>& target);
		virtual void Listen(const Vec3& targetPos) = 0;
	};

}

//endbasecross