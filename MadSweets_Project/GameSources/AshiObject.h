/*!
@file AshiObject.h
@brief AshiObject
�S���ҁF�ێR �T��
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
		void CreateTactile();  //�ǉ��p�̐G�o�̐���

	public:

		AshiObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross