/*!
@file TitleNameCtrl.h
@brief TitleNameCtrl
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "FadeCtrlBase.h"

namespace basecross {

	using itbs::Utility::Delegate;

	class TitleNameCtrl : public FadeCtrlBase
	{
		ex_weak_ptr<UIObject> m_fontUI;
		ex_weak_ptr<UIObject> m_chocoUI;

		float m_speed = 1.0f;
		bool m_isEnd = false;

		std::function<void(TitleNameCtrl&)> m_updateFunc;

		void UpdateChoco();
		void EndProcess();

	public:

		TitleNameCtrl(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<UIObject>& fontUI,
			const std::shared_ptr<UIObject>& chocoUI
		) :
			FadeCtrlBase(objPtr),m_fontUI(fontUI),m_chocoUI(chocoUI)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void FadeInStart() override {};
		void FadeOutStart() override;

		//アクセッサ----------------------------------------------------------------
		void SetSpeed(const float& speed) {
			m_speed = speed;
		}
		float GetSpeed() const {
			return m_speed;
		}

		bool IsEnd() const {
			return m_isEnd;
		}
	};

}

//endbasecross