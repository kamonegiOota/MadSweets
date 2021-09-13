/*!
@file ScalePop.cpp
@brief ScalePopのクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "ScalePop.h"

namespace basecross {

	bool ScalePop::IsStopScale(const Vec3& scale ,const Vec3& targetScale) {
		Vec3 between = targetScale - scale;

		float betweenSize = 0.1f;

		if (abs(between.x) <= betweenSize &&
			abs(between.y) <= betweenSize)
		{  //最大スケールになったら。
			return true;
		}

		return false;
	}

	void ScalePop::ScaleUpdate() {
		if (m_speed == 0.0f) {
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();
		m_elapsed += delta * m_speed;

		auto rad = sinf(m_elapsed);

		auto setScale = m_maxScale * rad;

		if (m_elapsed >= 1.0f) {   //一度最大になったら
			if (IsStopScale(setScale, m_returnScale)) {
				setScale = m_returnScale;
				m_elapsed = 0.0f;
				m_speed = 0.0f;
			}
		}

		auto trans = GetGameObject()->GetComponent<RectTransform>();
		trans->SetScale(Vec2(setScale));
	}

	void ScalePop::OnUpdate() {
		ScaleUpdate();
	}

}

//endbasecross