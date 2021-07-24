
/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "ThrowObject.h"

namespace basecross {

	class ThrowHandyObject : public ThrowObject	{

	public:

		ThrowHandyObject(const std::shared_ptr<Stage>& stage)
			:ThrowObject(stage)
		{}

		void OnCreate() override;

	};

}

//endbasecross