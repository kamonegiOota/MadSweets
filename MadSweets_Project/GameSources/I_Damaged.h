/*!
@file ChaseEnemyObject.h
@brief ChaseEnemyObject
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//ダメージを受ける側のインターフェース
	class I_Damaged {

	public:

		virtual void Damage(const float& damage) = 0;
	};

}

//endbasecross