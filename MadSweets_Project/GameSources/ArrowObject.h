
/*!
@file ArrowObject.h
@brief ArrowObject�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class ArrowObject : public GameObject
	{

	public:

		ArrowObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross