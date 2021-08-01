/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "Mathf.h"
#include "DebugObject.h"

namespace basecross {

	class SoundCookie : public Component
	{
		int m_numCrack = 2;  //ヒビ割れる回数

		void SendListener();  //音を聞くものに送信
		void MakeSound();  //音を出す処理
		void Crack(); //ひび割れ

	public:
		SoundCookie(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}
		
		void OnCreate() override;
		void OnUpdate() override;

		void OnCollisionEnter(std::shared_ptr<GameObject>& ohter) override;

		//アクセッサ-----------------------------------------------------


	};

}

//endbasecross