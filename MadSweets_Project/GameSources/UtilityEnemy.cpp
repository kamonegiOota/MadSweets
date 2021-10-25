/*!
@file BaseEnemy.cpp
@brief BaseEnemy‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "BaseEnemy.h"

#include "UtilityEnemy.h"

namespace basecross {

	map<wstring, vector<UtilityEnemy::CreateEnemyParam>> UtilityEnemy::sm_enemyParam = {
		{L"Stage1.csv",
			{
				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Handy, L"HandyPlowling"),

				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Cara, L"CaraPlowling"),

				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Ashi, L"AshiPlowling"),
			}
		},

		{L"Stage2.csv",
			{
				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Handy, L"HandyPlowling"),

				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Cara, L"CaraPlowling"),
			}
		},

		{L"Stage3.csv",
			{
				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Handy, L"HandyPlowling"),

				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Cara, L"CaraPlowling"),

				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Gra, L"GraPlowling"),
			}
		},
	};

}