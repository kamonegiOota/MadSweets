/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "I_Damaged.h"

namespace basecross {

	class LockPlayer : public Component
	{

	public:
		LockPlayer(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override {}

		/// <summary>
		/// Plyaer�̑����Active�ɂ��邩�ǂ���
		/// </summary>
		void SetPlayerOperationActive(bool isLock);

	};

}

//endbasecross