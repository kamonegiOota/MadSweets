#pragma once
#include "stdafx.h"

namespace basecross {

	namespace maru {
		class Mathf
		{

		public:

			/// <summary>
			/// X�����ɓn���ꂽVec3��rad����]���������l��Ԃ�
			/// </summary>
			/// <param name="vec">��]���������x�N�g��</param>
			/// <param name="rad">��]���������p�x</param>
			/// <returns>��]�������x�N�g��</returns>
			static Vec3 Mat4RotationAxisX(const Vec3& vec, const float rad);
			/// <summary>
			/// X������mat4x4��rad����]������B
			/// </summary>
			/// <param name="mat">��]��������mad4x4</param>
			/// <param name="rad">��]���������p�x</param>
			/// <returns>��]������4x4</returns>
			static Mat4x4 Mat4RotationAxisX(const Mat4x4& mat, const float rad);

			/// <summary>
			/// Y�����ɓn���ꂽVec3��rad����]���������l��Ԃ�
			/// </summary>
			/// <param name="vec">��]���������x�N�g��</param>
			/// <param name="rad">��]���������p�x</param>
			/// <returns>��]�������x�N�g��</returns>
			static Vec3 Mat4RotationAxisY(const Vec3& vec, const float rad);
			/// <summary>
			/// Y������mat4x4��rad����]������B
			/// </summary>
			/// <param name="mat">��]��������mad4x4</param>
			/// <param name="rad">��]���������p�x</param>
			/// <returns>��]������4x4</returns>
			static Mat4x4 Mat4RotationAxisY(const Mat4x4& mat, const float rad);

			/// <summary>
			/// Z������mat4x4��rad����]������B
			/// </summary>
			/// <param name="mat">��]��������mad4x4</param>
			/// <param name="rad">��]���������p�x</param>
			/// <returns>��]������4x4</returns>
			static Mat4x4 Mat4RotationAxisZ(const Mat4x4& mat, const float rad);

			static Vec3 Lerp(const Vec3& startPos, const Vec3& endPos, const float endTime, const float elapsedTime);

			/// <summary>
			/// �傫�����̐��l��Ԃ�
			/// </summary>
			template<class T>
			static T Max(const T& a, const T& b) {
				return a > b ? a : b;
			}

			/// <summary>
			/// ���������̐��l��Ԃ�
			/// </summary>
			template<class T>
			static T Min(const T& a, const T& b) {
				return a < b ? a : b;
			}

			/// <summary>
			/// min,max�̊Ԃ̐�����Ԃ��B
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