
/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class MTestBox : public GameObject
	{

	public:
		MTestBox(const std::shared_ptr<Stage>& stage):
			GameObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross