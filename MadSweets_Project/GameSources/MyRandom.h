
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
			/// �����_���ȃx�N�g����Ԃ�
			/// </summary>
			/// <param name="min">�ŏ��l</param>
			/// <param name="max">�ő�l</param>
			/// <returns>�����_���ȃx�N�g��</returns>
			static Vec3 RandomVector(const Vec3& min, const Vec3& max) {
				Vec3 randomPosition(0.0f);

				randomPosition.x = Random(min.x, max.x);
				randomPosition.y = Random(min.y, max.y);
				randomPosition.z = Random(min.z, max.z);

				return randomPosition;
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

			/// <summary>
			/// �����_���ȃ|�W�V������Ԃ��B
			/// </summary>
			/// <param name="maxRangeBase">�ő�l�̃x�[�X�l</param>
			/// <returns>�����_���ȃ|�W�V����</returns>
			static Vec3 RandomPosition(const Vec3& maxRangeBase) {
				auto maxRange = Vec3(abs(maxRangeBase.x), abs(maxRangeBase.y), abs(maxRangeBase.z));

				return RandomVector(-maxRange, maxRange);
			}

		};
	}

}

//endbasecross