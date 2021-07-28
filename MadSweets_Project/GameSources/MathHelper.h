#pragma once
#include<cmath>
#include<type_traits>

namespace itbs
{
	namespace Math
	{
		class MyMath
		{
		public:
			/// <summary>
			/// ��ׂčő��Ԃ�
			/// </summary>
			/// <param name="a">�v�f1</param>
			/// <param name="b">�v�f2</param>
			/// <returns>���傫���l</returns>
			template<class T, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t> = nullptr>
			static T Max(const T& a, const T& b)
			{
				return a > b ? a : b;
			}

			/// <summary>
			/// ��ׂčŏ���Ԃ�
			/// </summary>
			/// <param name="a">�v�f1</param>
			/// <param name="b">�v�f2</param>
			/// <returns>��菬�����l</returns>
			template<class T, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t> = nullptr>
			static T Min(const T& a, const T& b)
			{
				return a < b ? a : b;
			}

			/// <summary>
			/// �l��͈͐������ĕԂ�
			/// </summary>
			/// <param name="value">�l</param>
			/// <param name="min">�ŏ�</param>
			/// <param name="max">�ő�</param>
			/// <returns>�͈͐��������l</returns>
			template<class T, std::enable_if_t<std::is_arithmetic_v<T>, std::nullptr_t> = nullptr>
			static T Clamp(T value, const T& min, const T& max)
			{
				value = Min<T>(value, max);
				value = Max<T>(value, min);

				return value;
			}
		};
	}
}