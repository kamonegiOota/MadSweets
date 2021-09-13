/*!
@file ScalePop.cpp
@brief ScalePop�̃N���X����
�S���F�ێR�T��
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
		{  //�ő�X�P�[���ɂȂ�����B
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

		if (m_elapsed >= 1.0f) {   //��x�ő�ɂȂ�����
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