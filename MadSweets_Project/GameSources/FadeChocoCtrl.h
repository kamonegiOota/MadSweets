
/*!
@file MaruStage.h
@brief MaruStage
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

		Vec2 m_uiSize = Vec2(1280.0f, 800.0f);

		float m_speed = 3000.0f;
		bool m_isEnd = false;


		void CreateChocoUI();

		void FadeUpdate();
		void EndProcess();

	public:
		FadeChocoCtrl(const std::shared_ptr<GameObject>& objPtr)
			:FadeCtrlBase(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void FadeStart() override;

		//アクセッサ--------------------------------------------------------
		bool IsEnd() const {
			return m_isEnd;
		}
	};

}

//endbasecross