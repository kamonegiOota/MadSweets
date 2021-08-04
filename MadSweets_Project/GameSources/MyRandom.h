
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

			template<class T>
			static T Random(const T& min, const T& max)
			{
				std::uniform_real_distribution<> dist(min, max);

				auto value = static_cast<T>(dist(m_mt));

				return value;
			}

			//何割の確率化変数で受け取る。
			//0～100までの間の数値を引き数で受け取る。
			static bool RandomProbability(const float prob) {
				auto random = MyRandom::Random(0.0f, 100.0f);
				if (random <= prob) {
					return true;
				}
				else {
					return false;
				}
			}

			template<class T>
			static T RandomArray(const vector<T>& vec) {
				auto ran = MyRandom::Random(0, (int)vec.size() - 1);

				return vec[ran];
			}
			//static int RandomInt(const int min,const int max);

		};
	}

}

//endbasecross