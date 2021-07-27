/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
’S“–ÒFŠÛR —TŠì
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class EscapeEnemyObject : public GameObject
	{
		void CreatePlowlingRoute();

	public:

		EscapeEnemyObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross