/*!
@file AlphaFadeCtrl.h
@brief AlphaFadeCtrlクラス
担当：丸山裕喜
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
		std::function<bool(float& alpha)> m_isEndFunc;  //終了を判断する関数

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
		/// <summary>
		/// 強制的にフェードアウトさせる。
		/// </summary>
		/// <param name="startAlpha">透明化の初期値</param>
		void ForceFadeInStart(const float& startAlpha = 1.0f);
		void FadeOutStart() override;

		//アクセッサ------------------------------------------------------

		void SetSpeed(const float& speed) {
			m_speed = speed;
		}

		void SetTextureResource(const wstring& texture) {
			auto image = m_fadeObj->GetComponent<Image>();
			image->SetTextureResource(texture);
		}

		void SetFadeObj(const std::shared_ptr<UIObject>& uiObj) {
			m_fadeObj = uiObj;
		}
	};

}

//endbasecross