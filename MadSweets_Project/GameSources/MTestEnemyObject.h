/*!
@file BaseEnemy.cpp
@brief BaseEnemyÀ‘Ì
’S“–ÒFŠÛR —TŠì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class MTestEnemyObject : public GameObject
	{


	public:
		MTestEnemyObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross