
/*!
@file NumberObject.h
@brief NumberObject�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class NumberObject : public GameObject {

	public:

		NumberObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
	};

}

//endbasecross