/*!
@file ScalePop.h
@brief ScalePopヘッダ　
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class ScalePop : public Component
	{
		Vec3 m_maxScale;
		Vec3 m_returnScale;
		float m_speed;

		float m_elapsed = 0.0f;

		/// <summary>
		/// スケールの変動が終了したかどうかを判断
		/// </summary>
		/// <param name="scale">現在のスケール</param>
		/// <param name="targetScale">目標のスケール</param>
		/// <returns>終了するならtrue</returns>
		bool IsStopScale(const Vec3& scale, const Vec3& targetScale);

		void ScaleUpdate();

	public:

		ScalePop(const std::shared_ptr<GameObject>& objPtr):
			Component(objPtr),
			m_maxScale(Vec3(1.35f)),
			m_returnScale(Vec3(1.0f)),
			m_speed(0.0f)
		{}

		void OnCreate() override {}
		void OnUpdate() override;

		//アクセッサ-------------------------------------------------------------------------

		void SetMaxScale(const Vec3& scale) {
			m_maxScale = scale;
		}

		void SetReturnScale(const Vec3& scale) {
			m_returnScale = scale;
		}

		void SetSpeed(const float speed) {
			m_speed = speed;
		}

		void StartPop(const float& speed, const float& startScaleSize = 0.0f) {
			m_speed = speed;
			m_elapsed = startScaleSize;
		}
	};

}

//endbasecross