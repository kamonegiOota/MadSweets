/*!
@file ChaseEnemyObject.h
@brief ChaseEnemyObject
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//�_���[�W���󂯂鑤�̃C���^�[�t�F�[�X
	class I_Damaged {

	public:

		virtual void Damage(const float& damage) = 0;
	};

}

//endbasecross