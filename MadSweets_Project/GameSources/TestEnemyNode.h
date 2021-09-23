
/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
’S“–ÒFŠÛR —TŠì
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "EnemyStateNodeBase.h"
#include "MTestEnemy.h"

namespace basecross {

	class TestEnemyNode : public EnemyStateNodeBase<MTestEnemy>
	{

	public:

		TestEnemyNode(const std::shared_ptr<MTestEnemy>& enemy)
			:EnemyStateNodeBase<MTestEnemy>(enemy)
		{}

		void OnStart() override;
		void OnUpdate() override;
		void OnExit() override;

	};

}

//endbasecorss