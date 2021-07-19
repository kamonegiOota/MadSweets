/*!
@file LoseTarget.h
@brief LoseTarget
’S“–ÒFŠÛR —TŠì
*/
#pragma once

#include "stdafx.h"
#include "Project.h"

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	class EnState_LoseTarget : public maru::StateMachine<BaseEnemy>
	{

	public:

		EnState_LoseTarget(const std::shared_ptr<BaseEnemy>& owner)
			:maru::StateMachine<BaseEnemy>(owner)
		{}

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

	};

}

//endbasecorss