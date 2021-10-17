/*!
@file BaseEnemy.h
@brief BaseEnemy
íSìñé“ÅFä€éR óTäÏ
*/

#pragma once

#include "StateMachine.h"

namespace basecross {

	class UtilityEnemy {

	public:

		enum class EnemyType {
			Handy,
			Gra,
			Ashi,
			Cara,
		};

		struct CreateEnemyParam {
			EnemyType type;
			wstring plowlingDataName;
			vector<Vec3> plowPositions;

			CreateEnemyParam(const EnemyType type,
				const wstring plowlingDataName
			)
				:type(type), plowlingDataName(plowlingDataName)
			{}
		};

		static map<wstring, vector<UtilityEnemy::CreateEnemyParam>> sm_enemyParam;


	};

}