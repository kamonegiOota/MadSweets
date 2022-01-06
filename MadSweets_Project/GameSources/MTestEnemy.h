/*!
@file MTestEnemy.h
@brief MTestEnemy
’S“–ÒFŠÛR —TŠì
*/

#pragma once

#include "stdafx.h"
#include "Project.h"
#include "BaseEnemy.h"

namespace basecross {

	class MTestEnemy : public BaseEnemy
	{
		

	public:

		MTestEnemy(const std::shared_ptr<GameObject>& objPtr)
			:BaseEnemy(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;
			
	};

}

//endbasecross