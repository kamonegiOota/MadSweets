/*!
@file MaruStage.cpp
@brief MaruStage����
�S���ҁF�ێR �T��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class BaseEnemy :public Component
	{

	public:
		
		BaseEnemy(const std::shared_ptr<GameObject> objPtr)
			:Component(objPtr)
		{}

	};

}

//endbasecross