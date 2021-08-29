
/*!
@file LoadData.h
@brief ロードデータヘッダ　
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "AlphaFadeCtrl.h"
#include "AlphaFadeObject.h"

namespace basecross {

	class LoadStageTrigger : public Component
	{
		ex_weak_ptr<AlphaFadeCtrl> m_fadeCtrl;
		std::shared_ptr<GameObject> m_target;

		wstring m_nextMap = L"Stage2.csv";
		Vec3 m_position = Vec3(0.0f);

		void MovePosition();
		void ChangeStage();
		void FadeStart();

	public:
		LoadStageTrigger(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override {}
		
		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;

		//アクセッサ---------------------------------------------------------------
		void SetNextMap(const wstring& nextMap) {
			m_nextMap = nextMap;
		}

		void SetMovePosition(const Vec3& position) {
			m_position = position;
		}
	};

}

//basecross