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

	class SoundCookie : public Component
	{
		int m_numCrack = 2;  //�q�r������

		void DestProcess();  //���������o�Ȃ��Ƃ��̏���
		void SendListener();  //���𕷂����̂ɑ��M
		void MakeSound();  //�����o������
		void Crack(); //�Ђъ���

	public:
		SoundCookie(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr),m_numCrack(2)
		{}
		
		void OnCreate() override;
		void OnUpdate() override;

		void OnCollisionEnter(std::shared_ptr<GameObject>& ohter) override;

		//�A�N�Z�b�T-----------------------------------------------------
		//���񉹂��o�邩���Z�b�g����B
		void SetNumCrack(const int& num) {
			m_numCrack = num;
		}
		int GetNumCrack() const {
			return m_numCrack;
		}

	};

}

//endbasecross