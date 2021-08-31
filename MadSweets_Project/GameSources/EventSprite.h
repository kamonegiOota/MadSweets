/*!
@file BillBoard.h
@brief BillBoardクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "AlphaFadeCtrl.h"

namespace basecross {

	class EventSprite : public Component
	{
		bool m_isUpdate = false;

		ex_weak_ptr<AlphaFadeCtrl> m_fadeCtrl;

		ex_weak_ptr<Image> m_image;
		vector<wstring> m_sprites;
		int m_index = 0;

		float m_timeElapsed = 0;
		float m_time = 5.0f;

		void ChangeStage();

		void CreateImage();
		void CreateFadeCtrl();

		void EndProcess();
		void NextSprite();
		void InputMgr() {}
		void TimeMgr();

	public:
		EventSprite(const std::shared_ptr<GameObject>& objPtr,
			const vector<wstring>& sprites
		) :
			Component(objPtr),m_sprites(sprites)
		{}

		void OnCreate() override;
		void OnStart() override;
		void OnUpdate() override;

		void EventStart();
		//アクセッサ--------------------------------------------------

		void SetTime(const float& time) {
			m_time = time;
		}
	};

}

//endbasecross