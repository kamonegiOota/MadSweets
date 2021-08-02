/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "Mathf.h"
#include "DebugObject.h"

namespace basecross {

	class FlameMatch : public Component
	{

	public:

		FlameMatch(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override;

		/// <summary>
		/// �Q�[���X�^�[�g
		/// </summary>
		void StartGame();
	};

}

//endbasecross