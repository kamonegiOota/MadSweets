/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
’S“–ÒFŠÛR —TŠì
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class GraObject : public GameObject 
	{
		void CreatePlowlingRoute();
		void CreateTactile();  //•Ç‰ñ”ğ—p‚ÌGŠo‚Ì¶¬

	public:
		GraObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecorss