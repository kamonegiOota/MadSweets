/*!
@file BaseEnemy.h
@brief BaseEnemy
�S���ҁF�ێR �T��
*/

#pragma once

#include "BaseEnemy.h"
#include "I_Chase.h"

namespace basecross {

	/// <summary>
	/// �G����������ǂ������Ă���G�l�~�[
	/// </summary>
	class ChaseEnemy : public BaseEnemy, public I_Chase
	{

	public:
		ChaseEnemy(const std::shared_ptr<GameObject>& objPtr)
			:BaseEnemy(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		//Interface�̎���
		void ChangeChaseState(const std::shared_ptr<GameObject>& target) override;

		//�A�N�Z�b�T-----------------------------------------------
	};
}

//endbasecross