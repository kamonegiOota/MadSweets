#include"MathHelper.h"

namespace itbs
{
	namespace Math
	{
		float MyMath::Clamp(const float value, const float min, const float max)
		{
			float result = value;
			result = std::fminf(result, max);
			result = std::fmaxf(result, min);

			return result;
		}
	}
}