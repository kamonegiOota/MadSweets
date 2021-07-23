/*!
@file BaseEnemy.h
@brief BaseEnemy
�S���ҁF�ێR �T��
*/

#pragma once

#include "BaseEnemy.h"
#include "StateMachine.h"
#include "I_Escape.h"

namespace basecross {

	/// <summary>
	/// �v���C���\���������瓦���铮�������Enemy
	/// </summary>
	class EscapeEnemy : public BaseEnemy, public I_Escape
	{

	public:

		EscapeEnemy(const std::shared_ptr<GameObject>& objPtr)
			:BaseEnemy(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		//�C���^�[�t�F�[�X�̎���
		void ChangeEscapeState(const std::shared_ptr<GameObject>& target) override;
		void SuccessEscape() override;

		//void EyeSearch();  //�ڂ̃T�[�`
	};

}

//endbasecross