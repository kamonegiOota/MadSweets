/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
’S“–ÒFŠÛR —TŠì
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class CaraObject : public GameObject
	{
		void CreatePlowlingRoute();
		void CreateTactile();  //•Ç‰ñ”ğ—p‚ÌGŠo‚Ì¶¬
		
	public:
		CaraObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
	};

}

//endbasecross