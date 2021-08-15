/*!
@file MaruStage.h
@brief MaruStage
íSìñé“ÅFä€éR óTäÏ
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "TitleNameCtrl.h"
#include "FadeChocoCtrl.h"

namespace basecross {

	class TitleFadeCtrl : public Component
	{
		ex_weak_ptr<TitleNameCtrl> m_titleNameCtrl;
		ex_weak_ptr<FadeChocoCtrl> m_fadeChocoCtrl;

		void ChangeStage();

	public:
		TitleFadeCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override {}

		void FadeStart();

	};

}

//endbasecross