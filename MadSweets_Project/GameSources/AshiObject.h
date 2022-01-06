/*!
@file AshiObject.h
@brief AshiObject
’S“–ÒFŠÛR —TŠì
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "AnimationHelper.h"
#include"Trigger.h"

namespace basecross {

	class AshiObject : public GameObject
	{
		void CreatePlowlingRoute();
		void CreateTactile();  //•Ç‰ñ”ğ—p‚ÌGŠo‚Ì¶¬

	public:

		AshiObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross