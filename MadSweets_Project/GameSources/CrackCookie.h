/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "Mathf.h"
#include "DebugObject.h"
#include "PlayerWeightMgr.h"

namespace basecross {

	/// <summary>
	/// ���񐔓��񂾂����N�b�L�[
	/// </summary>
	class CrackCookie : public Component
	{
		enum class CrackState {
			Normal,
			Crack,
			Crash,
		};

		/// <summary>
		/// �ϋv�x
		/// </summary>
		float m_durability = 2.0f;
		float m_maxDurability = m_durability;
		vector<wstring> m_textures;

		/// <summary>
		/// ����ϋv�l���v�Z���ĕԂ�
		/// </summary>
		/// <param name="weightMgr">PlayerWieghtMgr�̖{��</param>
		/// <returns>����ϋv�l��Ԃ�</returns>
		float CalucDamage(const std::shared_ptr<PlayerWeightMgr>& weightMgr);
		void DestProcess();
		/// <summary>
		/// �e�N�X�`���̕ύX���K�v���`�F�b�N
		/// </summary>
		void TextureCheck();
		/// <summary>
		/// �ϋv�l�����炷����
		/// </summary>
		/// <param name="damage">����ϋv�l</param>
		void Crack(const float& damage);

	public:

		CrackCookie(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override{}

		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;
	};

}

//endbasecross