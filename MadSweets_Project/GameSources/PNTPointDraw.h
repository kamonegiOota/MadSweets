/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
íSìñé“ÅFä€éR óTäÏ
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