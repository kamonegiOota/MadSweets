/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
íSìñé“ÅFä€éR óTäÏ
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class PNTPointDraw : Component
	{

	public :
		PNTPointDraw(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override{}

		void OnDraw() override;

	};

}

//endbasecross