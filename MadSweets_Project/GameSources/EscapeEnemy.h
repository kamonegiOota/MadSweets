/*!
@file BaseEnemy.h
@brief BaseEnemy
�S���ҁF�ێR �T��
*/

#pragma once

#include "BaseEnemy.h"
#include "StateMachine.h"

namespace basecross {

	/// <summary>
	/// �v���C���\���������瓦���铮�������Enemy
	/// </summary>
	class EscapeEnemy : public BaseEnemy
	{

	public:

		EscapeEnemy(const std::shared_ptr<GameObject>& objPtr)
			:BaseEnemy(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};

}

//endbasecross