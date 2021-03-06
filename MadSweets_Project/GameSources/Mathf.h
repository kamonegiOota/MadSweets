
/*!
@file Mathf.h
@brief Mathfクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	namespace maru {
		class Mathf
		{

		public:

			/// <summary>
			/// Xを軸に渡されたVec3をrad分回転させた数値を返す
			/// </summary>
			/// <param name="vec">回転させたいベクトル</param>
			/// <param name="rad">回転させたい角度</param>
			/// <returns>回転させたベクトル</returns>
			static Vec3 Mat4RotationAxisX(const Vec3& vec, const float rad);
			/// <summary>
			/// Xを軸にmat4x4をrad分回転させる。
			/// </summary>
			/// <param name="mat">回転させたいmad4x4</param>
			/// <param name="rad">回転させたい角度</param>
			/// <returns>回転させた4x4</returns>
			static Mat4x4 Mat4RotationAxisX(const Mat4x4& mat, const float rad);

			/// <summary>
			/// Yを軸に渡されたVec3をrad分回転させた数値を返す
			/// </summary>
			/// <param name="vec">回転させたいベクトル</param>
			/// <param name="rad">回転させたい角度</param>
			/// <returns>回転させたベクトル</returns>
			static Vec3 Mat4RotationAxisY(const Vec3& vec, const float rad);
			/// <summary>
			/// Yを軸にmat4x4をrad分回転させる。
			/// </summary>
			/// <param name="mat">回転させたいmad4x4</param>
			/// <param name="rad">回転させたい角度</param>
			/// <returns>回転させた4x4</returns>
			static Mat4x4 Mat4RotationAxisY(const Mat4x4& mat, const float rad);

			/// <summary>
			/// Zを軸にmat4x4をrad分回転させる。
			/// </summary>
			/// <param name="mat">回転させたいmad4x4</param>
			/// <param name="rad">回転させたい角度</param>
			/// <returns>回転させた4x4</returns>
			static Mat4x4 Mat4RotationAxisZ(const Mat4x4& mat, const float rad);

			static Vec3 Lerp(const Vec3& startPos, const Vec3& endPos, const float endTime, const float elapsedTime);

			/// <summary>
			/// 大きい方の数値を返す
			/// </summary>
			template<class T>
			static T Max(const T& a, const T& b) {
				return a > b ? a : b;
			}

			/// <summary>
			/// 小さい方の数値を返す
			/// </summary>
			template<class T>
			static T Min(const T& a, const T& b) {
				return a < b ? a : b;
			}

			/// <summary>
			/// min,maxの間の数字を返す。
			/// </summary>
			template<class T>
			static T Clamp(const T& value, const T& min, const T& max) {
				T reValue = value;

				if (reValue < min) {
					reValue = min;
				}

				if (reValue > max) {
					reValue = max;
				}

				return reValue;
			}

		};
	}

	

}