/*!
@file MaruStage.h
@brief MaruStage
íSìñé“ÅFä€éR óTäÏ
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "TitleNameCtrl.h"

namespace basecross {

	class TitleFadeCtrl : public Component
	{
		ex_weak_ptr<TitleNameCtrl> m_titleNameCtrl;

		std::function<void(TitleFadeCtrl&)> m_updateFunc;

		void ChangeStage();
		void ChangeStageMgr();

	public:
		TitleFadeCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override;

		void FadeStart();

	};

}

//endbasecross