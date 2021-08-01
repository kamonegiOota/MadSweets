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

		void DestProcess();  //もう音が出ないときの処理
		void SendListener();  //音を聞くものに送信
		void MakeSound();  //音を出す処理
		void Crack(); //ひび割れ

	public:
		SoundCookie(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr),m_numCrack(2)
		{}
		
		void OnCreate() override;
		void OnUpdate() override;

		void OnCollisionEnter(std::shared_ptr<GameObject>& ohter) override;

		//アクセッサ-----------------------------------------------------
		//何回音が出るかをセットする。
		void SetNumCrack(const int& num) {
			m_numCrack = num;
		}
		int GetNumCrack() const {
			return m_numCrack;
		}

	};

}

//endbasecross