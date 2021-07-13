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
			/// 値を範囲制限して返す
			/// </summary>
			/// <param name="value">値</param>
			/// <param name="min">最小</param>
			/// <param name="max">最大</param>
			/// <returns>範囲制限した値</returns>
			static float Clamp(const float value, const float min, const float max);
		};
	}
}