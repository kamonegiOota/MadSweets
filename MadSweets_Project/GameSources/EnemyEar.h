/*!
@file PlowlingMove.h
@brief PlowlingMove
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "EarBase.h"

namespace basecross {

	class EnemyEar : public EarBase
	{

	public:
		EnemyEar(const std::shared_ptr<GameObject>& objPtr)
			:EarBase(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override;

	};

}

//endbasecross