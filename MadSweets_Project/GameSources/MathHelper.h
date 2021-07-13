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
			/// ’l‚ğ”ÍˆÍ§ŒÀ‚µ‚Ä•Ô‚·
			/// </summary>
			/// <param name="value">’l</param>
			/// <param name="min">Å¬</param>
			/// <param name="max">Å‘å</param>
			/// <returns>”ÍˆÍ§ŒÀ‚µ‚½’l</returns>
			static float Clamp(const float value, const float min, const float max);
		};
	}
}