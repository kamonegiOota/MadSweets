
/*!
@file NumbersCtrl.h
@brief NumbersCtrl�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "NumberObject.h"

namespace basecross {

	class NumbersCtrl : public Component 
	{
		int m_value = 0;
		//�ő包��
		int m_maxDigit = 3;

		vector<ex_weak_ptr<NumberObject>> m_numberObjs;

		void CreateNumberObjs();

		/// <summary>
		/// ����Ȃ�0�͔�\���ɂ���B
		/// </summary>
		void ChangeDrawNumbers();
		/// <summary>
		/// �i���o�[�̃|�W�V�������Z�b�g����B
		/// </summary>
		void SetNumbersPosition();

	public:

		NumbersCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		NumbersCtrl(const std::shared_ptr<GameObject>& objPtr, const int& maxDigit)
			:Component(objPtr),m_maxDigit(maxDigit)
		{}

		void OnCreate() override;
		void OnStart() override {}
		void OnUpdate() override {}


		//�A�N�Z�b�T--------------------------------------------------------

		void SetValue(const int& value);
		int GetValue() const {
			return m_value;
		}

		/// <summary>
		/// �\������ő包���̐ݒ�
		/// </summary>
		/// <param name="digit">�ő包��</param>
		//void SetMaxDigit(const int& digit) {
		//	m_maxDigit = digit;
		//}
		//int GetMaxDigit() const {
		//	return m_maxDigit;
		//}
	};

}

//endbasecross