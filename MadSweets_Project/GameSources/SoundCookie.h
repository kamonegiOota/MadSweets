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

		void SendListener();  //���𕷂����̂ɑ��M
		void MakeSound();  //�����o������
		void Crack(); //�Ђъ���

	public:
		SoundCookie(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}
		
		void OnCreate() override;
		void OnUpdate() override;

		void OnCollisionEnter(std::shared_ptr<GameObject>& ohter) override;

		//�A�N�Z�b�T-----------------------------------------------------


	};

}

//endbasecross