/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"
#include "EnemyEar.h"

namespace basecross {

	void EnemyEar::OnUpdate() {

	}

	void EnemyEar::SoundListen(const std::shared_ptr<GameObject>& target) {
		m_astar = GetGameObject()->GetComponent<AstarCtrl>();
		if (m_astar) {
			m_astar->SearchAstarStart(target);
		}
	}

	void EnemyEar::SoundListen(const Vec3& targetPos) {
		m_astar = GetGameObject()->GetComponent<AstarCtrl>();
		if (m_astar) {
			m_astar->SearchAstarStart(targetPos);
		}
	}
}

//endbasecross