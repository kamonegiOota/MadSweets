
/*!
@file GameTimer.h
@brief GameTimerクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class GameTimer {
	public:

		struct Parametor {
			float intervalTime = 0.0f;
			float elapsedTime = 0.0f;
			std::function<void()> endFunc = nullptr;

			Parametor(float intervalTime, const std::function<void()>& func);

			/// <summary>
			/// タイム終了時にする処理
			/// </summary>
			/// <param name="isEndFunc">終了関数を呼び出すかどうか</param>
			void EndTimer(bool isEndFunc = true);
		};

	private:

		Parametor m_param;

	public:

		GameTimer(const float& intervalTime, const std::function<void()>& func);
		GameTimer(const Parametor& param = Parametor(0.0f, nullptr));

		/// <summary>
		/// 時間の更新
		/// </summary>
		/// <param name="countSpeed">更新時間のspeed</param>
		/// <returns>Update終了時にtrueを返す</returns>
		bool UpdateTimer(const float& countSpeed = 1.0f);

		/// <summary>
		/// 経過時間リセット
		/// </summary>
		void ResetTimer() {
			m_param.elapsedTime = 0.0f;
		}

		/// <summary>
		/// 経過時間リセット
		/// </summary>
		/// <param name="intervalTime">設定時間</param>
		void ResetTimer(const float& intervalTime) {
			ResetTimer(intervalTime, nullptr);
		}

		/// <summary>
		/// 経過時間リセット
		/// </summary>
		/// <param name="intervalTime">設定時間</param>
		/// <param name="func">終了時に呼び出したいイベント</param>
		void ResetTimer(const float& intervalTime, const std::function<void()>& func) {
			m_param.intervalTime = intervalTime;
			m_param.endFunc = func;
			m_param.elapsedTime = 0.0f;
		}

		/// <summary>
		/// 強制終了
		/// </summary>
		/// <param name="isEndFunc">終了時に呼び出すイベントを呼び出すかどうか</param>
		void ForceEndTimer(const bool isEndFunc) {
			m_param.EndTimer(isEndFunc);
		}

		//アクセッサ-------------------------------------------

		//経過時間を超えたかどうか
		bool IsTimeUp() {
			return m_param.intervalTime <= m_param.elapsedTime;
		}

		//経過時間 / 設定時間 == 経過時間の割合
		float GetTimeRate() {
			if (IsTimeUp()) {
				return 1.0f;
			}

			return m_param.elapsedTime / m_param.intervalTime;
		}

		//1.0f - ( 経過時間 / 設定時間 )
		float GetIntervalTimeRate() {
			return 1.0f - GetTimeRate();
		}

		//残り時間
		float GetLeftTime() {
			return m_param.intervalTime - m_param.elapsedTime;
		}

		//経過時間
		float GetElapsedTime() {
			return m_param.elapsedTime;
		}

		//設定時間
		float GetIntervalTime() {
			return m_param.intervalTime;
		}
	};

}

//endbasecross