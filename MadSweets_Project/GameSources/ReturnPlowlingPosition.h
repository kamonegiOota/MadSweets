/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//�p�j��Ԃ̏ꏊ�܂Ŗ߂�R���|�[���l���g
	class ReturnPlowlingPosition : public Component
	{

	public:

		ReturnPlowlingPosition(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;
	};

}

//endbasecross