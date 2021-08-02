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

	/// <summary>
	/// ���񐔓��񂾂����N�b�L�[
	/// </summary>
	class CrackCookie : public Component
	{
		/// <summary>
		/// �ϋv�x
		/// </summary>
		float m_durability = 2.0f;

		void DestProcess();
		void Crack(const float& damage);

	public:

		CrackCookie(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override{}

		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;
	};

}

//endbasecross