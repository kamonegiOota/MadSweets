#pragma once
#include<cmath>

namespace itbs
{
	namespace Math
	{
		class MyMath
		{
		public:
			/// <summary>
			/// �l��͈͐������ĕԂ�
			/// </summary>
			/// <param name="value">�l</param>
			/// <param name="min">�ŏ�</param>
			/// <param name="max">�ő�</param>
			/// <returns>�͈͐��������l</returns>
			static float Clamp(const float value, const float min, const float max);
		};
	}
}