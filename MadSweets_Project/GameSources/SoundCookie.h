/*!
@file SoundCookie.h
@brief SoundCookieクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "Mathf.h"
#include "DebugObject.h"

namespace basecross {

	class SoundCookie : public Component
	{
		enum class CrackState {
			Normal,
			Crack,
			Crash,
		};

		vector<wstring> m_textures;

		int m_numCrack = 2;  //ヒビ割れる回数
		int m_maxNumCrack = m_numCrack;

		/// <summary>
		/// テクスチャの変更が必要か判断して変える
		/// </summary>
		void TextureCheck();
		/// <summary>
		/// もう音が出ないときの処理
		/// </summary>
		void DestProcess();
		/// <summary>
		/// 音を聞くオブジェクトに、音が出たことを伝える
		/// </summary>
		void SendListener();
		/// <summary>
		/// 音を鳴らす
		/// </summary>
		void MakeSound();
		/// <summary>
		/// 耐久値を減らす
		/// </summary>
		void Crack();

	public:
		SoundCookie(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr),m_numCrack(2)
		{}
		
		void OnCreate() override;
		void OnUpdate() override;

		void OnCollisionEnter(std::shared_ptr<GameObject>& ohter) override;

		//アクセッサ-----------------------------------------------------
		
		/// <summary>
		/// 耐久値のセット
		/// </summary>
		/// <param name="num">耐久値</param>
		void SetNumCrack(const int& num) {
			m_numCrack = num;
		}
		int GetNumCrack() const {
			return m_numCrack;
		}

	};

}

//endbasecross