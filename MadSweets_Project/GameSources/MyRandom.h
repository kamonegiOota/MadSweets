
/*!
@file MyRandom.h
@brief MyRandomクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"
#include <random>

namespace basecross {

	namespace maru {
		class MyRandom
		{
			static std::mt19937 m_mt;

		public:

			/// <summary>
			/// 渡された最大と最少の値から、ランダムな値を返す。
			/// </summary>
			template<class T>
			static T Random(const T& min, const T& max)
			{
				std::uniform_real_distribution<> dist(min, max);

				auto value = static_cast<T>(dist(m_mt));

				return value;
			}

			/// <summary>
			/// 何割の確率化変数で受け取る。
			/// 0～100までの間の数値を引き数で受け取る。
			/// </summary>
			/// <param name="prob">確率</param>
			/// <returns>確率でtrueかfalseを返す</returns>
			static bool RandomProbability(const float prob) {
				auto random = MyRandom::Random(0.0f, 100.0f);
				if (random <= prob) {
					return true;
				}
				else {
					return false;
				}
			}

			/// <summary>
			/// 配列の中からランダムな要素を返す。
			/// </summary>
			template<class T>
			static T RandomArray(const vector<T>& vec) {
				auto ran = MyRandom::Random(0, (int)vec.size() - 1);

				return vec[ran];
			}

		};
	}

}

//endbasecross