/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"
#include "EnemyEar.h"

namespace basecross {

	bool EnemyEar::IsListenRnage(const Vec3& targetPos) {
		auto toVec = targetPos - transform->GetPosition();

		//•·‚±‚¦‚é”ÍˆÍ“à‚É‚¢‚½‚çtrue‚ğ•Ô‚·B
		return toVec.length() < m_listenRange ? true : false;
	}

	void EnemyEar::SoundListen(const std::shared_ptr<GameObject>& target) {
		auto targetPos = target->GetComponent<Transform>()->GetPosition();

		SoundListen(targetPos);
	}

	void EnemyEar::SoundListen(const Vec3& targetPos) {
		if (IsListenRnage(targetPos)) {  //•·‚±‚¦‚é”ÍˆÍ‚É‚¢‚é
			auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
			if (astar) {
				astar->SearchAstarStart(targetPos);
			}
		}
	}
}

//endbasecross