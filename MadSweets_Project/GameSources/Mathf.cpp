
#include "stdafx.h"
#include "Project.h"
#include "Mathf.h"

namespace basecross {

	namespace maru {
		Vec3 Mathf::Mat4RotationAxisX(const Vec3& vec, const float rad)
		{
			Mat4x4 rotMat = {
				{1,0,0,0},
				{0,cosf(rad),-sinf(rad) ,0},
				{0,sinf(rad),cosf(rad),0},
				{0,0,0,1}
			};

			return vec * rotMat;
		}

		//Mat4*4用
		Mat4x4 Mathf::Mat4RotationAxisX(const Mat4x4& mat, const float rad)
		{
			Mat4x4 rotMat = {
				{1,0,0,0},
				{0,cosf(rad),-sinf(rad) ,0},
				{0,sinf(rad),cosf(rad),0},
				{0,0,0,1}
			};

			return mat * rotMat;
		}


		Vec3 Mathf::Mat4RotationAxisY(const Vec3& vec, const float rad)
		{
			Mat4x4 rotMat = {
				{cosf(rad),0,sinf(rad),0},
				{0,1,0,0},
				{-sinf(rad),0,cosf(rad),0},
				{0,0,0,1},
			};

			return vec * rotMat;
		}

		Mat4x4 Mathf::Mat4RotationAxisY(const Mat4x4& mat, const float rad)
		{
			Mat4x4 rotMat = {
				{cosf(rad),0,sinf(rad),0},
				{0,1,0,0},
				{-sinf(rad),0,cosf(rad),0},
				{0,0,0,1},
			};

			return mat * rotMat;
		}

		Mat4x4 Mathf::Mat4RotationAxisZ(const Mat4x4& mat, const float rad)
		{
			Mat4x4 rotMat = {
				{cosf(rad),-sinf(rad),0,0},
				{sinf(rad),cosf(rad),0,0},
				{0,0,1,0},
				{0,0,0,1},
			};

			return mat * rotMat;
		}

		Vec3 Mathf::Lerp(const Vec3& startPos, const Vec3& endPos, const float endTime, const float elapsedTime)
		{
			if (endTime <= elapsedTime)  //基底以上の数値が入っていたら、動かさない。
			{
				return Vec3(0.0f);
			}

			auto toEnd = endPos - startPos;

			auto returnPos = toEnd / endTime * elapsedTime;

			return returnPos;
		}
	}
}