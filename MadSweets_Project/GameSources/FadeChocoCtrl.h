
/*!
@file FadeChocoCtrl.h
@brief FadeChocoCtrl
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "TitleNameCtrl.h"

#include "FadeCtrlBase.h"

namespace basecross {

	class FadeChocoCtrl : public FadeCtrlBase
	{
		ex_weak_ptr<UIObject> m_ui;

		std::function<void(FadeChocoCtrl&)> m_updateFunc;
		std::function<void(FadeChocoCtrl&, float& height)> m_updateEndFunc;

		Vec2 m_uiSize = Vec2(1280.0f, 800.0f);

		float m_direct = 1.0f;
		float m_speed = 5000.0f;
		float m_maxSize = 8000.0f;
		bool m_isEnd = false;

		void CreateChocoUI();

		void FadeUpdate();
        void EndFadeIn(float& height);
		void EndFadeOut(float& height);

		void EndProcess();

	public:
		FadeChocoCtrl(const std::shared_ptr<GameObject>& objPtr)
			:FadeCtrlBase(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void FadeInStart() override;
		void FadeOutStart() override;

		//アクセッサ--------------------------------------------------------
		bool IsEnd() const {
			return m_isEnd;
		}

		void SetDirect(const float& direct) {
			m_direct = direct;
		}

		void SetAnchor(const AnchorType& anchorType) {
			m_ui->GetComponent<RectTransform>()->SetAnchor(anchorType);
		}

		void SetSpeed(const float& speed) {
			m_speed = speed;
		}
	};

}

//endbasecross