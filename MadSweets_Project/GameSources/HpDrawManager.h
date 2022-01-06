/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class HpDrawManager : public Component
	{
		ex_weak_ptr<Image> m_image;

		float m_drawRatio = 0.3f;  //�\�����銄��

		void CreateImage();

		bool IsDraw(const float& ratio);
		/// <summary>
		/// �摜�̃A���t�@�l���v�Z���Ă����
		/// </summary>
		/// <returns>�A���t�@�l��Ԃ�</returns>
		float CalucAlpha();
		void ImageAlphaManager();

	public:

		HpDrawManager(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		
		//�A�N�Z�b�T------------------------------------------------

	};

}

//endbasecross