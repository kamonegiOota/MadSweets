
/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	struct WaitTimerParametor
	{
		float time = 1.0f;       //時間
		float timeElapsed = 0;   //時間経過
		float countSpeed = 1.0f; //時間を数えるスピード
		std::function<void()> endAction = nullptr; //終了時に呼び出す関数ポインタ
		bool isEnd = false;      //終了しているかどうか

		WaitTimerParametor(const float& time, const float& countSpeed,const
			std::function<void()>& endAction = nullptr
		) :
			time(time), countSpeed(countSpeed), endAction(endAction)
		{}

		/// <summary>
		/// タイム終了時にする処理
		/// </summary>
		/// <param name="isEndAction">終了関数を呼び出すかどうか</param>
		void EndTimer(const bool isEndAction = true) {
			timeElapsed = time;
			isEnd = true;

			if (isEndAction) {
				if (endAction) {
					endAction();
				}
			}

			endAction = nullptr;
		}
	};


	class WaitTimer : public Component
	{
		std::map<type_index, std::shared_ptr<WaitTimerParametor>> m_params;

		void TimerUpdate();

	public:

		WaitTimer(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override;

		/// <summary>
		/// 強制的に待機状態を解除する時に使用する関数
		/// </summary>
		/// <param name="tPtr">待機処理を行いたいclassのポインタ</param>
		/// <param name="time">待機する時間</param>
		/// <param name="endAction">終了時に呼び出す関数</param>
		/// <param name="countSpeed">時間をカウントするスピード</param>
		template<class T>
		void AddTimer(const std::shared_ptr<T> tPtr,
			const float& time, const std::function<void()>& endAction = nullptr, const float& countSpeed = 1.0f)
		{
			auto tIndex = type_index(typeid(tPtr));

			auto newData = make_shared<WaitTimerParametor>(time, countSpeed, endAction);
			m_params[tIndex] = newData;
		}

		/// <summary>
		/// 待機状態か判断して返す。
		/// </summary>
		/// <param name="tPtr">待機処理を行いたいclassのポインタ</param>
		template<class T>
		bool IsWait(const std::shared_ptr<T>& tPtr) 
		{
			auto tIndex = type_index(typeid(tPtr));

			//自分のタイプが設定されていたら
			if (m_params.count(tIndex) != 0) {
				return !m_params[tIndex]->isEnd; //終了状態でないならtrue(待機状態)
			}
			else {
				return false; //登録されてないならそもそも待機しない。
			}
		}

		/// <summary>
		/// 強制的に待機状態を解除する時に使用する関数
		/// </summary>
		/// <param name="tPtr">待機処理を行いたいclassのポインタ</param>
		/// <param name="isEndAction">終了関数を呼び出すかどうか</param>
		template<class T>
		void AbsoluteEndTimer(const std::shared_ptr<T>& tPtr, const bool isEndAction) 
		{
			auto tIndex = type_index(typeid(tPtr));

			if (m_params.count(tIndex) == 0) { //設定されていなかったら
				return;  //処理をしない。
			}

			m_params[tIndex]->EndTimer(isEndAction);
		}

	};

}

//endbasecross