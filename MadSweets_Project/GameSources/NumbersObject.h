
/*!
@file NumbersObject.h
@brief NumbersObject�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//�����̐����������I�u�W�F�N�g
	class NumbersObject : public GameObject
	{

	public:
		NumbersObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross