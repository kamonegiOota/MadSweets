
/*!
@file MaruStage.h
@brief MaruStage
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "TitleNameCtrl.h"

namespace basecross {

	class FadeChocoCtrl : public Component
	{
		ex_weak_ptr<UIObject> m_ui;

		Vec2 m_uiSize = Vec2(1280.0f, 800.0f);

		float m_speed = 0.0f;
		bool m_isEnd = false;

		void CreateChocoUI();

		void FadeUpdate();

	public:
		FadeChocoCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void FadeStart(const float& speed = 3000.0f);

		//�A�N�Z�b�T--------------------------------------------------------
		bool IsEnd() const {
			return m_isEnd;
		}
	};

}

//endbasecross