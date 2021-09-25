/*!
@file I_Chase.h
@brief I_Chase
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "BaseEnemy.h"

namespace basecross {

	class I_Chase
	{
	public:
		virtual void ChangeChaseState(const std::shared_ptr<GameObject>& target) = 0;  //�ǂ������鏈���ɕύX���鎞
		virtual void ChangeTargetLostState(const std::shared_ptr<GameObject>& target) = 0;  //�^�[�Q�b�g�����������Ƃ��̏���
	};
}

//endbasecross