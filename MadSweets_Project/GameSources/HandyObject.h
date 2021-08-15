/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
�S���ҁF�ێR �T��
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "AnimationHelper.h"
#include"Trigger.h"

namespace basecross {

	class HandyObject : public GameObject
	{
		void CreatePlowlingRoute();

	public:
		HandyObject(std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

		//������
		void OnUpdate() override;
	};

}

//endbasecross