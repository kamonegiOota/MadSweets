#pragma once
#include "stdafx.h"

namespace basecross {

	namespace maru {
		class Mathf
		{

		public:
			//Mathf();

			//static Vec3 matrixAxisY(Vec3 vec, float rad);

			//static Vec3 matrixAxisX(Vec3 vec, float rad);

			//Mathf��Matrix4*4�o�[�W����
			static Vec3 Mat4RotationAxisX(const Vec3& vec, const float rad);
			static Mat4x4 Mat4RotationAxisX(const Mat4x4& mat, const float rad);  //mat4*4��rad����]������B

			static Vec3 Mat4RotationAxisY(const Vec3& vec, const float rad);
			static Mat4x4 Mat4RotationAxisY(const Mat4x4& mat, const float rad);  //mat4*4��rad����]������B

			static Mat4x4 Mat4RotationAxisZ(const Mat4x4& mat, const float rad);  //mat4*4��rad����]������B

			static Vec3 Lerp(const Vec3& startPos, const Vec3& endPos, const float endTime, const float elapsedTime);

			template<class T>
			static T Max(const T& a, const T& b) {  //�傫������Ԃ�
				return a > b ? a : b;
			}

			template<class T>
			static T Min(const T& a, const T& b) {   //����������Ԃ��B
				return a < b ? a : b;
			}

			template<class T>
			static T Clamp(const T& value, const T& min, const T& max) {  //min,max�̊Ԃ̐�����Ԃ��B
				T reValue = value;
				reValue = MyMathf::Min(reValue);
				reValue = MyMathf::Max(reValue);

				return reValue;
			}

		};
	}

	

}