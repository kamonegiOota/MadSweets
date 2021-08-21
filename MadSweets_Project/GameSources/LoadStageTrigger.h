
/*!
@file LoadData.h
@brief ロードデータヘッダ　
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "FadeChocoCtrl.h"

namespace basecross {

	class LoadStageTrigger : Component
	{
		ex_weak_ptr<FadeChocoCtrl> m_chocoCtrl;

		void ChangeStage();
		void FadeStart();

	public:
		LoadStageTrigger(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override {}
		
		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;

	};

}

//basecross