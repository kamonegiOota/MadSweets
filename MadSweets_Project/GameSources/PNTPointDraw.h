/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class PNTPointDraw :public BcBaseDraw
	{

	public :
		PNTPointDraw(const std::shared_ptr<GameObject>& objPtr)
			:BcBaseDraw(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override{}

		void OnDraw() override;

	};

}

//endbasecross