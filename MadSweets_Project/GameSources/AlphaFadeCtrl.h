/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "FadeCtrlBase.h"

namespace basecross {

	class AlphaFadeCtrl : public FadeCtrlBase
	{
		bool m_isUpdate = false;

		float m_direct = 0.0f;
		float m_speed = 1.0f;
		std::shared_ptr<UIObject> m_fadeObj;
		std::function<bool(float& alpha)> m_isEndFunc;  //�I���𔻒f����֐�

		void SetStartImageAlpha(const float& alpha);
		void EndProcess();
		void FadeUpdate();

	public:
		AlphaFadeCtrl(const std::shared_ptr<GameObject>& objPtr)
			:FadeCtrlBase(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;


		void FadeInStart() override;
		void FadeOutStart() override;

		//�A�N�Z�b�T------------------------------------------------------
		void SetSpeed(const float& speed) {
			m_speed = speed;
		}

		void SetTextureResource(const wstring& texture) {
			auto image = m_fadeObj->GetComponent<Image>();
			image->SetTextureResource(texture);
		}
	};

}

//endbasecross