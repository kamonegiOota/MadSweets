/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class HpDrawMgr : public Component
	{
		ex_weak_ptr<Image> m_image;

		float m_drawRatio = 0.3f;  //�\�����銄��

		void CreateImage();

		bool IsDraw(const float& ratio);
		float CalucAlpha();
		void ImageAlphaMgr();

	public:

		HpDrawMgr(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		
		//�A�N�Z�b�T------------------------------------------------

	};

}

//endbasecross