/*!
@file SoundCookie.h
@brief SoundCookie�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "Mathf.h"
#include "DebugObject.h"

namespace basecross {

	class SoundCookie : public Component
	{
		enum class CrackState {
			Normal,
			Crack,
			Crash,
		};

		vector<wstring> m_textures;

		int m_numCrack = 2;  //�q�r������
		int m_maxNumCrack = m_numCrack;

		/// <summary>
		/// �e�N�X�`���̕ύX���K�v�����f���ĕς���
		/// </summary>
		void TextureCheck();
		/// <summary>
		/// ���������o�Ȃ��Ƃ��̏���
		/// </summary>
		void DestProcess();
		/// <summary>
		/// ���𕷂��I�u�W�F�N�g�ɁA�����o�����Ƃ�`����
		/// </summary>
		void SendListener();
		/// <summary>
		/// ����炷
		/// </summary>
		void MakeSound();
		/// <summary>
		/// �ϋv�l�����炷
		/// </summary>
		void Crack();

	public:
		SoundCookie(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr),m_numCrack(2)
		{}
		
		void OnCreate() override;
		void OnUpdate() override;

		void OnCollisionEnter(std::shared_ptr<GameObject>& ohter) override;

		//�A�N�Z�b�T-----------------------------------------------------
		
		/// <summary>
		/// �ϋv�l�̃Z�b�g
		/// </summary>
		/// <param name="num">�ϋv�l</param>
		void SetNumCrack(const int& num) {
			m_numCrack = num;
		}
		int GetNumCrack() const {
			return m_numCrack;
		}

	};

}

//endbasecross