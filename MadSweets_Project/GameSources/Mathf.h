#pragma once
#include "stdafx.h"

namespace basecross {

	namespace maru {
		class Mathf
		{

		public:

			/// <summary>
			/// X‚ğ²‚É“n‚³‚ê‚½Vec3‚ğrad•ª‰ñ“]‚³‚¹‚½”’l‚ğ•Ô‚·
			/// </summary>
			/// <param name="vec">‰ñ“]‚³‚¹‚½‚¢ƒxƒNƒgƒ‹</param>
			/// <param name="rad">‰ñ“]‚³‚¹‚½‚¢Šp“x</param>
			/// <returns>‰ñ“]‚³‚¹‚½ƒxƒNƒgƒ‹</returns>
			static Vec3 Mat4RotationAxisX(const Vec3& vec, const float rad);
			/// <summary>
			/// X‚ğ²‚Émat4x4‚ğrad•ª‰ñ“]‚³‚¹‚éB
			/// </summary>
			/// <param name="mat">‰ñ“]‚³‚¹‚½‚¢mad4x4</param>
			/// <param name="rad">‰ñ“]‚³‚¹‚½‚¢Šp“x</param>
			/// <returns>‰ñ“]‚³‚¹‚½4x4</returns>
			static Mat4x4 Mat4RotationAxisX(const Mat4x4& mat, const float rad);

			/// <summary>
			/// Y‚ğ²‚É“n‚³‚ê‚½Vec3‚ğrad•ª‰ñ“]‚³‚¹‚½”’l‚ğ•Ô‚·
			/// </summary>
			/// <param name="vec">‰ñ“]‚³‚¹‚½‚¢ƒxƒNƒgƒ‹</param>
			/// <param name="rad">‰ñ“]‚³‚¹‚½‚¢Šp“x</param>
			/// <returns>‰ñ“]‚³‚¹‚½ƒxƒNƒgƒ‹</returns>
			static Vec3 Mat4RotationAxisY(const Vec3& vec, const float rad);
			/// <summary>
			/// Y‚ğ²‚Émat4x4‚ğrad•ª‰ñ“]‚³‚¹‚éB
			/// </summary>
			/// <param name="mat">‰ñ“]‚³‚¹‚½‚¢mad4x4</param>
			/// <param name="rad">‰ñ“]‚³‚¹‚½‚¢Šp“x</param>
			/// <returns>‰ñ“]‚³‚¹‚½4x4</returns>
			static Mat4x4 Mat4RotationAxisY(const Mat4x4& mat, const float rad);

			/// <summary>
			/// Z‚ğ²‚Émat4x4‚ğrad•ª‰ñ“]‚³‚¹‚éB
			/// </summary>
			/// <param name="mat">‰ñ“]‚³‚¹‚½‚¢mad4x4</param>
			/// <param name="rad">‰ñ“]‚³‚¹‚½‚¢Šp“x</param>
			/// <returns>‰ñ“]‚³‚¹‚½4x4</returns>
			static Mat4x4 Mat4RotationAxisZ(const Mat4x4& mat, const float rad);

			static Vec3 Lerp(const Vec3& startPos, const Vec3& endPos, const float endTime, const float elapsedTime);

			/// <summary>
			/// ‘å‚«‚¢•û‚Ì”’l‚ğ•Ô‚·
			/// </summary>
			template<class T>
			static T Max(const T& a, const T& b) {
				return a > b ? a : b;
			}

			/// <summary>
			/// ¬‚³‚¢•û‚Ì”’l‚ğ•Ô‚·
			/// </summary>
			template<class T>
			static T Min(const T& a, const T& b) {
				return a < b ? a : b;
			}

			/// <summary>
			/// min,max‚ÌŠÔ‚Ì”š‚ğ•Ô‚·B
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