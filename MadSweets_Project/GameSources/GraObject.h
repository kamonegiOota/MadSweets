/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class GraObject : public GameObject 
	{
		void CreatePlowlingRoute();
		void CreateTactile();  //�ǉ��p�̐G�o�̐���

	public:
		GraObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecorss