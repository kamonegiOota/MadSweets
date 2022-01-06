
/*!
@file NumbersCtrl.h
@brief NumbersCtrlクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "NumberObject.h"

namespace basecross {

	class NumbersCtrl : public Component 
	{
		int m_value = 0;
		//最大桁数
		int m_maxDigit = 3;

		vector<ex_weak_ptr<NumberObject>> m_numberObjs;

		void CreateNumberObjs();

		/// <summary>
		/// いらない0は非表示にする。
		/// </summary>
		void ChangeDrawNumbers();
		/// <summary>
		/// ナンバーのポジションをセットする。
		/// </summary>
		void SetNumbersPosition();

	public:

		NumbersCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		NumbersCtrl(const std::shared_ptr<GameObject>& objPtr, const int& maxDigit)
			:Component(objPtr),m_maxDigit(maxDigit)
		{}

		void OnCreate() override;
		void OnStart() override {}
		void OnUpdate() override {}


		//アクセッサ--------------------------------------------------------

		void SetValue(const int& value);
		int GetValue() const {
			return m_value;
		}

		/// <summary>
		/// 表示する最大桁数の設定
		/// </summary>
		/// <param name="digit">最大桁数</param>
		//void SetMaxDigit(const int& digit) {
		//	m_maxDigit = digit;
		//}
		//int GetMaxDigit() const {
		//	return m_maxDigit;
		//}
	};

}

//endbasecross