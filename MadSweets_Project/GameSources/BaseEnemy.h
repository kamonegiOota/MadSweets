/*!
@file BaseEnemy.cpp
@brief BaseEnemyÀ‘Ì
’S“–ÒFŠÛR —TŠì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class BaseEnemy :public Component
	{

	public:
		
		BaseEnemy(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnDraw() override {}

	};

}

//endbasecross