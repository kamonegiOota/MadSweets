/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "EnemyEar.h"

namespace basecross {

	bool EnemyEar::IsListenRnage(const Vec3& targetPos) {
		auto toVec = targetPos - transform->GetPosition();

		//聞こえる範囲内にいたらtrueを返す。
		return toVec.length() < m_listenRange ? true : false;
	}

	void EnemyEar::SoundListen(const std::shared_ptr<GameObject>& target) {
		auto targetPos = target->GetComponent<Transform>()->GetPosition();

		SoundListen(targetPos);
	}

	void EnemyEar::SoundListen(const Vec3& targetPos) {
		if (IsListenRnage(targetPos)) {  //聞こえる範囲にいる時
			auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
			if (astar) {
				astar->SearchAstarStart(targetPos);
			}
		}
	}
}

//endbasecross