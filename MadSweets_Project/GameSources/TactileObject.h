/*!
@file PlowlingMove.h
@brief PlowlingMove
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class TactileObject : public GameObject
	{

	public:

		TactileObject(const std::shared_ptr<Stage>& stage) 
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross