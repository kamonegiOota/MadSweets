/*!
@file SearchObject.h
@brief SearchObject�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//�����I�ɂ�����œG�̐؂�ւ����s����悤�ɂ���B
	class EyeSearchLange : public Component
	{

	public:
		EyeSearchLange(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {};
		void OnUpdate() override {};

	};

}

//endbasecross