#pragma once
#include<random>

namespace itbs
{
	namespace Math
	{
		class Random
		{
			static std::mt19937 mt;

		public:
			/// <summary>
			/// �ŏ��l�ƍő�l�̊Ԃ������_���ŕԂ�
			/// </summary>
			/// <param name="min">�ŏ��l</param>
			/// <param name="max">�ő�l</param>
			/// <returns>�ŏ��l�ƍő�l�̊Ԃ̃����_���Ȓl</returns>
			static float Range(const float min, const float max);
			/// <summary>
			/// ���m����true��Ԃ�
			/// </summary>
			/// <param name="probability">�m��</param>
			/// <returns>�������true,�͂�����false</returns>
			static bool Probability(float probability);
		};
	}
}