
/*!
@file MyRandom.h
@brief MyRandom�N���X
�S���F�ێR�T��
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
			/// �n���ꂽ�ő�ƍŏ��̒l����A�����_���Ȓl��Ԃ��B
			/// </summary>
			template<class T>
			static T Random(const T& min, const T& max)
			{
				std::uniform_real_distribution<> dist(min, max);

				auto value = static_cast<T>(dist(m_mt));

				return value;
			}

			/// <summary>
			/// �����̊m�����ϐ��Ŏ󂯎��B
			/// 0�`100�܂ł̊Ԃ̐��l���������Ŏ󂯎��B
			/// </summary>
			/// <param name="prob">�m��</param>
			/// <returns>�m����true��false��Ԃ�</returns>
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
			/// �z��̒����烉���_���ȗv�f��Ԃ��B
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