/*!
@file BaseEnemy.h
@brief BaseEnemy
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"

namespace basecross {

	class UtilityEnemy {

	public:

		enum class EnemyType {
			Handy,
			Gra,
			Cara
		};

		struct CreateEnemyParam {
			EnemyType type;
			vector<Vec3> plowPositions;

			CreateEnemyParam(const EnemyType type,
				vector<Vec3> plowPositions
			)
				:type(type), plowPositions(plowPositions)
			{}
		};

		static map<wstring, vector<UtilityEnemy::CreateEnemyParam>> sm_enemyParam;


	};

}