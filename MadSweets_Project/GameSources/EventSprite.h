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
		ex_weak_ptr<AlphaFadeCtrl> m_fadeCtrl;

		ex_weak_ptr<Image> m_image;
		vector<wstring> m_sprites;
		int m_index = 0;

		void ChangeStage();
		void CreateImage();
		void CreateFadeCtrl();

		void EndProcess();
		void NextSprite();
		void InputMgr();

	public:
		EventSprite(const std::shared_ptr<GameObject>& objPtr,
			const vector<wstring>& sprites
		) :
			Component(objPtr),m_sprites(sprites)
		{}

		void OnCreate() override {}
		void OnStart() override;
		void OnUpdate() override;


		//アクセッサ--------------------------------------------------


	};

}

//endbasecross