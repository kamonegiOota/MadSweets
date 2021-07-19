/*!
@file ChaseEnemyObject.h
@brief ChaseEnemyObject
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class ChaseEnemyObject : public GameObject
	{
		void CreatePlowlingRoute();

	public:

		ChaseEnemyObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
	};

}

//endbasecross