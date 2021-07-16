/*!
@file SearchObject.h
@brief SearchObjectなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//将来的にこちらで敵の切り替えを行えるようにする。
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