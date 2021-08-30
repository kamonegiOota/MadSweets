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
				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Handy,
					{
						Vec3(0.0f),
						Vec3(0.0f)
					}
				),

				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Cara,
					{
						Vec3(0.0f),
						Vec3(0.0f)
					}
				),
			}
		},

		{L"Stage2.csv",
			{
				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Handy,
					{
						Vec3(0.0f),
						Vec3(0.0f)
					}
				),

				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Cara,
					{
						Vec3(0.0f),
						Vec3(0.0f)
					}
				),
			}
		},

		{L"Stage3.csv",
			{
				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Handy,
					{
						Vec3(0.0f),
						Vec3(0.0f)
					}
				),

				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Cara,
					{
						Vec3(0.0f),
						Vec3(0.0f)
					}
				),

				UtilityEnemy::CreateEnemyParam(UtilityEnemy::EnemyType::Gra,
					{
						Vec3(0.0f),
					}
				),
			}
		},
	};

}