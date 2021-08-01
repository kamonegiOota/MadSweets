/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "EnemyEar.h"

#include "EnState_TargetChase.h"
#include "EnState_CheckSoundPos.h"

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
		
		//特定のステートの時は変更できないようにする。
		//敵を直接見ているときは目の前の敵を見るなど

		if (IsListenRnage(targetPos)) {  //聞こえる範囲にいる時
			auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
			if (enemy) {
				enemy->ChangeStateMachine<EnState_CheckSoundPos>(targetPos);
			}
		}
	}
}

//endbasecross