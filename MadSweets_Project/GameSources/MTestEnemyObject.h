/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
’S“–ÒFŠÛR —TŠì
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class MTestEnemyObject : public GameObject
	{


	public:
		MTestEnemyObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross