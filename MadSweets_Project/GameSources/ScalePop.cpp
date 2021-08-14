/*!
@file ScalePop.cpp
@brief ScalePop�̃N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"
#include "ScalePop.h"

namespace basecross {

	bool ScalePop::StopScale(const Vec3& scale ,const Vec3& targetScale) {
		Vec3 between = targetScale - scale;

		float betweenSize = 0.1f;

		if (abs(between.x) <= betweenSize &&
			abs(between.y) <= betweenSize)
		{  //�ő�X�P�[���ɂȂ�����B
			return true;
		}

		return false;
	}

	bool ScalePop::IsMinScale(const Vec3& nowScale) {
		if (abs(nowScale.x) < m_minScale.x &&
			abs(nowScale.y) < m_minScale.y)
		{  //�ő�X�P�[���ɂȂ�����B
			return true;
		}
		return false;
	}

	void ScalePop::OnCreate() {

	}

	void ScalePop::OnUpdate() {
		if (m_speed == 0.0f) {
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();
		m_elapsed += delta * m_speed;

		auto rad = sinf(m_elapsed);
		
		auto trans = GetGameObject()->GetComponent<RectTransform>();
		
		auto setScale = m_maxScale * rad;

		//if (IsMinScale(setScale)) {
		//	setScale = m_minScale;
		//}

		if (m_elapsed >= 1.0f) {   //��x�ő�ɂȂ�����
			if (StopScale(setScale, m_returnScale)) {
				setScale = m_returnScale;
				m_elapsed = 0.0f;
				m_speed = 0.0f;
			}
		}

		trans->SetScale(Vec2(setScale));
	}

}

//endbasecross